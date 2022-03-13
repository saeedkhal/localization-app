from sklearn.metrics import accuracy_score
from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split
import pandas as pd

data = pd.read_csv('all_data.csv')
X = data.iloc[:, :-1]
y = data.iloc[:, -1]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.4, random_state=0)

classifier = XGBClassifier()
classifier.fit(X_train, y_train)

y_pred = classifier.predict(X_test)
print('test:', accuracy_score(y_test, y_pred))

y_pred = classifier.predict(X_train)
print('train:', accuracy_score(y_train, y_pred))

classifier.save_model('xg_boost.model')
