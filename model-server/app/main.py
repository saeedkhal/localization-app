from flask import Flask, request
import numpy as np
import json
from xgboost import XGBClassifier
import datetime
ct = datetime.datetime.now()
try:
    classifier = XGBClassifier()
    classifier.load_model('xg_boost.model')
except:
    print(f"{ct} - ERROR - couldn't load the classifier, or model")

app = Flask(__name__)


@app.route("/", methods=["POST"])
def localize():
    ct = datetime.datetime.now()
    try:
        body = json.loads(request.data)
    except:
        print(f"{ct} - ERROR - data body schema is not correct")
    try:
        prediction = classifier.predict(np.array([body["strengthes"]]))
    except:
        print(f"{ct} - ERROR - couldn't predict the region")
    print(f'{ct} - DATA - {body["strengthes"]} - {prediction[0]}')
    return prediction[0]
