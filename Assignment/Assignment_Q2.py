import requests
import json
import pprint
data = requests.get('https://smart-reminder-web-app-ztisgbssmq-el.a.run.app/schedule')
data = data.json()
pprint.pprint(data)                         # for organised printing on terminal
with open("url_data.json", "w") as outfile:
    json.dump(data, outfile)
    print("json file created")
