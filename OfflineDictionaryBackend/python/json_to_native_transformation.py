# -*- coding: utf-8 -*-
"""
Created on Wed Aug  7 16:21:46 2024

@author: Anar
"""

import json
ENTITY_DELIM = b'\x01'#'\n'.encode('utf-8')#b'\x01';
SECTION_DELIM = b'\x02'#'@'.encode('utf-8')#b'\x02';
RECORD_DELIM = b'\x03'#'|'.encode('utf-8')#\x03';

def write_translations():
    file = open("C:\\Users\\Anar\\Downloads\\translations.json")
    content = json.load(file)
    file.close()
    
    c = 0
    for key in content.keys():
        c += 1
        print(key, c)
        try:
            result = key.encode('utf-8') + SECTION_DELIM
            for elem in content[key]:
                result += elem.encode('utf-8') + RECORD_DELIM
            filename = key[0]
            if (len(key) > 1):
                filename += key[1]
            file = open("C:\\Users\\Anar\\Downloads\\translations\\"+filename.lower(), "ba+")
            file.write(result[:-1] + ENTITY_DELIM)
            file.close()
        except:
            print("exception")

def write_examples():
    file = open("C:\\Users\\Anar\\Downloads\\examples.json", encoding="utf8")
    content = json.load(file)
    file.close()
    
    c = 0
    for key in content.keys():
        c += 1
        print(key, c)
        try:
            result = key.encode('utf-8') + SECTION_DELIM
            for elem in content[key]:
                result += elem.encode('utf-8') + RECORD_DELIM
            filename = key[0]
            if (len(key) > 1):
                filename += key[1]
            file = open("C:\\Users\\Anar\\Downloads\\examples\\"+filename.lower(), "ba+")
            file.write(result[:-1] + ENTITY_DELIM)
            file.close()
        except:
            print("exception")
            
def write_descriptions():
    file = open("C:\\Users\\Anar\\Downloads\\descriptions.json")
    content = json.load(file)
    file.close()
    
    c = 0
    for key in content.keys():
            c += 1
            print(key, c)
            try:
                result = key.encode('utf-8') + SECTION_DELIM
                for elem in content[key]:
                    for k in elem.keys():
                        result += k.encode('utf-8') + RECORD_DELIM + elem[k].encode('utf-8') + RECORD_DELIM
                    result = result[0:-1] + SECTION_DELIM
                filename = key[0]
                if (len(key) > 1):
                    filename += key[1]
                file = open("C:\\Users\\Anar\\Downloads\\descriptions\\"+filename.lower(), "ba+")
                file.write(result[:-1] + ENTITY_DELIM)
                file.close()
            except:
                print("exception")
                
write_examples()