import json
import requests
import time
from bs4 import BeautifulSoup

HEADERS = {"User-Agent": "Mozilla/5.0",
           "Content-Type": "application/json; charset=UTF-8"
           }
"""
supported_langs = {}

response = requests.get("https://context.reverso.net/translation/", headers=HEADERS)

soup = BeautifulSoup(response.content, features="lxml")

src_selector = soup.find("div", id="src-selector")
trg_selector = soup.find("div", id="trg-selector")

for selector, attribute in ((src_selector, "source_lang"),
                                    (trg_selector, "target_lang")):
            dd_spans = selector.find(class_="drop-down").find_all("span")
            langs = [span.get("data-value") for span in dd_spans]
            langs = [lang for lang in langs
                     if isinstance(lang, str) and len(lang) == 2]

            supported_langs[attribute] = tuple(langs)
#print(supported_langs)
"""
WORDS_FILE = "C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackend\\data\\words.txt"
FILENAME_EXAMPLES = f"C:\Job\StockSharp\OfflineDictionaryBackend\OfflineDictionaryBackend\data\examples.json"
FILENAME_TRANSLATIONS = "C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackend\\data\\translations.json"
CACHE = "parsed_words.txt"
ENTITY_DELIM = b'\x01';
SECTION_DELIM = b'\x02';
RECORD_DELIM = b'\x03';

PARSED_WORDS = set()
NUM_INCLUDED = 0
NUM_ALL = 0

def split_in_array(texts: list, delim: str):
    result = []
    for text in texts:
        result += text.split(delim)
    return result
    
def write_result(translations, examples):
    print("WRITING")
    with open(FILENAME_EXAMPLES, 'w+', encoding='utf-8') as f:
        json.dump(examples, f, ensure_ascii=False, indent=4)
            
    with open(FILENAME_TRANSLATIONS, 'w+', encoding='utf-8') as f:
        json.dump(translations, f, ensure_ascii=False, indent=4)
    
def parse (text_to_parse, depth = 1):
    global FILENAME
    global ENTITY_DELIM
    global SECTION_DELIM
    global RECORD_DELIM
    global PARSED_WORDS
    global NUM_INCLUDED
    global NUM_ALL
    global MAX_DEPTH

    result_examples = {}
    result_translations = {}
    
    for word in text_to_parse:
        try:
            NUM_ALL += 1
            print("word:", word)
            print("all: ", NUM_ALL)
            
            if word in PARSED_WORDS:
                print("already parsed")
                continue
            
            file = open(CACHE, "a+")
            file.write(','+word)
            file.close()
            
            PARSED_WORDS.add(word)
            data = {"source_lang": "nl", "target_lang": "en", "source_text": word, "target_text":""}
            try:
                response = requests.post("https://context.reverso.net/bst-query-service", headers=HEADERS, data=json.dumps(data))
            except:
                print("server doesn't respond, waiting")
                time.sleep(300)
            translations_json = response.json()["dictionary_entry_list"]
            examples_json = response.json()["list"]
            translations = [tr["term"] for tr in translations_json]
            examples = [ex["s_text"].replace("<em>", "").replace("</em>", "") for ex in examples_json]
            if (len(examples) > 20):
                examples = examples[0:20]
            if (len(examples) == 0 or len(translations) == 0):
                continue
            result_examples[word] = examples
            result_translations[word] = translations
            
        except:
            continue
        
        NUM_INCLUDED += 1
        print("included: ", NUM_INCLUDED)
        
        if (NUM_INCLUDED % 1000 == 0):
            write_result(result_translations, result_examples)
        time.sleep(0.2)
        
    write_result(result_translations, result_examples)

text = """In de leesautobiografie beschrijf je je leeservaringen tot nu toe.
Hieronder vind je aantal vragen die je jezelf kunt stellen bij het verzamelen van informatie voor je biografie."""
file = open(WORDS_FILE)
text = file.read()
file.close()

file = open(CACHE, "w+")
parsed = file.read().split(',')

for word in parsed:
    PARSED_WORDS.add(word)
file.close()

parse(text.split('\n'))

print("\nFINISHED")