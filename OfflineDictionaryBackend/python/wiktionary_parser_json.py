# -*- coding: utf-8 -*-
"""
Created on Sat Aug  3 15:05:18 2024

@author: Anar
"""

import json
import requests
from bs4 import BeautifulSoup
from lxml import etree
import time
import re
HEADERS = {"User-Agent": "Mozilla/5.0",
           "Content-Type": "application/json; charset=UTF-8"
           }

WORDS_FILE = "..\\data\\words.txt"
RESULT_FILE = "..\\data\\vervoegingen.json"

def write_result(result):
    print("WRITING")
    with open(RESULT_FILE, 'w+', encoding='utf-8') as f:
        json.dump(result, f, ensure_ascii=False, indent=4)

def parse(words): 
    def return_text_only(elem):
        x = etree.tostring(elem).decode('utf-8')
        result = "".join(re.split("\<|\>", x)[::2]).replace("\n", "")
        return result
        
    def parse_table(row, columns):
        result = {}
        i = 0
        for elem in row[1:]:
            text = return_text_only(elem)
            result[columns[i]] = text
            i+=1
        return result
            
    def parse_forms(tree):
        result = {}
        table = tree.xpath('/html/body/div[2]/div/div[3]/main/div[3]/div[3]/div[1]/table[1]/tbody')
        #print(etree.tostring(table))
            
        i = 0
        prev_row = []
        columns = []
        voltooid = False
        for row in table[0]:
            row_string = etree.tostring(row).decode('utf-8').lower()
            #print(row[0].text, '\n')
            if ("ik" in row_string and "jullie" in row_string):
                columns = []
                for elem in row[1:]:
                    columns.append(return_text_only(elem))
                continue
            
            t = etree.tostring(row[0]).decode("utf-8")
            if ("tegenwoordig" in t and "o.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
                    
            if ("verleden" in t and "o.v.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
            
            if ("toekomend" in t and "o.t.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
            
            if ("voorwaardelijk" in t and "o.v.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)

            if ("tegenwoordig" in t and "v.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
                    
            if ("verleden" in t and "v.v.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
            
            if ("toekomend" in t and "v.t.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
            
            if ("voorwaardelijk" in t and "v.v.t.t" in t):
                print("TXT", return_text_only(row[0]))
                tijd = return_text_only(row[0])
                if (tijd in result.keys()):
                    continue
                result[tijd] = parse_table(row, columns)
                
            prev_row = [row]
            i += 1    
        
        print(result)
        return result
    
    current_num = 0
    num_done = 0
    result = {}
    for word in words[6000:]:        
        print("\n\nWORD:", word)
        print("CURRENT_NUM:", current_num)
        print("NUM_DONE:", num_done)
        current_num += 1
        
        try:
            response = requests.post("https://nl.wiktionary.org/wiki/"+word+"/vervoeging", headers=HEADERS)
            tree = etree.HTML(response.text)
            result[word] = parse_forms(tree)
        except:
            continue
        
        num_done += 1
        if (current_num % 1 == 0):
            write_result(result)
        print("DONE")
        time.sleep(0.2)

file = open(WORDS_FILE)
text = file.read()
file.close()

text = text.split('\n')
parse(text)    

