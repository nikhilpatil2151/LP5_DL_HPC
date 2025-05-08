#!/usr/bin/env python
# coding: utf-8

# In[47]:


import pandas as pd


# In[48]:


import numpy as np


# In[49]:


import tensorflow as tf


# In[50]:


from tensorflow import keras


# In[51]:


from sklearn.model_selection import train_test_split


# In[52]:


from sklearn.preprocessing import StandardScaler


# In[53]:


import matplotlib.pyplot as plt


# In[54]:


data = pd.read_csv('boston.csv')


# In[55]:


data.columns


# In[56]:


X = data.drop('Price', axis = 1)


# In[57]:


y = data['Price']


# In[58]:


scaler = StandardScaler()


# In[59]:


X_scaled = scaler.fit_transform(X)


# In[60]:


X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size = 0.2, random_state = 42)


# In[61]:


model = keras.Sequential([
    keras.Input(shape = (X_train.shape[1],)),
    keras.layers.Dense(1)
])


# In[62]:


model.compile(optimizer = 'adam', loss = 'mse', metrics = ['mae'])


# In[63]:


history = model.fit(X_train, y_train, epochs = 100, validation_split = 0.2, verbose = 0)


# In[64]:


loss, mae = model.evaluate(X_test, y_test)


# In[65]:


y_pred = model.predict(X_test)


# In[66]:


y_pred[0:10]


# In[67]:


y_train[0:10]


# In[68]:


plt.figure(figsize=(8, 6))
plt.scatter(y_test, y_pred)
plt.xlabel("Actual Prices")
plt.ylabel("Predicted Prices")
plt.title("Actual VS Predicted House Prices")
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='red')  # Ideal line
plt.grid(True)
plt.show()


# In[ ]:





# In[ ]:





# In[ ]:




