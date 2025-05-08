#!/usr/bin/env python
# coding: utf-8

# In[3]:


from keras.datasets import imdb


# In[4]:


from keras.models import Sequential


# In[5]:


from keras.layers import Embedding, Flatten, Dense


# In[6]:


(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words = 10000)


# In[7]:


from keras.preprocessing.sequence import pad_sequences


# In[8]:


X_train = pad_sequences(X_train, maxlen = 200)
X_test = pad_sequences(X_test, maxlen = 200)


# In[9]:


model = Sequential([
    Embedding(input_dim = 10000, output_dim = 16, input_length = 200),
    Flatten(),
    Dense(16, activation = 'relu'),
    Dense(1, activation = 'sigmoid')
])


# In[10]:


model.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])


# In[11]:


model.fit(X_train, y_train, epochs = 5, batch_size = 512, validation_split = 0.2)


# In[12]:


loss, acc = model.evaluate(X_test, y_test)


# In[13]:


y_pred_prob = model.predict(X_test)


# In[14]:


y_pred_prob[0:5]


# In[15]:


y_pred_class = (y_pred_prob > 0.5).astype('int')


# In[16]:


for i in range(10) :
    print(f"Actual : {y_test[i]} Predicted : {y_pred_class[i][0]}")


# In[ ]:




