# -*- coding: utf-8 -*-
"""
Created on Thu Aug  1 16:08:13 2024

@author: Anar
"""
import json
import requests
from bs4 import BeautifulSoup
from lxml import etree
import time
HEADERS = {"User-Agent": "Mozilla/5.0",
           "Content-Type": "application/json; charset=UTF-8"
           }

WORDS_FILE = "..\\data\\words.txt"
RESULT_FILE = "..\\data\\descriptions.json"

def write_result(result):
    print("WRITING")
    with open(RESULT_FILE, 'w+', encoding='utf-8') as f:
        json.dump(result, f, ensure_ascii=False, indent=4)

def parse(words): 
    def parse_info_header(elem, num_headers):
        
        result = {"article":"", "type":elem.tail.strip()}
        fonts = elem.xpath("//font")
        for font in fonts:
            if (font.text == None):
                continue
            e = font.text.strip()
            if e == "het" or e == "de":
                result["article"] = e
        return result
    
    def parse_info(elem):
        result = []
        
        headers = elem.xpath("//h1")     
        
        for e in elem:
            if (e.tag == "h1"):
                result.append(parse_info_header(e, len(headers)))
        print(result)
        return result
    
    current_num = 0
    num_done = 0
    result = {}
    for word in words:        
        print("\n\nWORD:", word)
        print("CURRENT_NUM:", current_num)
        print("NUM_DONE:", num_done)
        current_num += 1
        try:
            response = requests.post("https://www.woorden.org/woord/"+word, headers=HEADERS)
            tree = etree.HTML(response.text)
            div = tree.xpath("/html/body/div[1]/div/div/div/div/div[2]/div[2]/div")
            result[word] = parse_info(div[0])
        except:
            continue
        num_done += 1
        if (current_num % 1000 == 0):
            write_result(result)
        print("DONE")
        time.sleep(0.2)

file = open(WORDS_FILE)
text = file.read()
file.close()


text = text.split('\n')
parse(text)    



