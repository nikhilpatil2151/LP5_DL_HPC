#!/usr/bin/env python
# coding: utf-8

# In[1]:


from keras.datasets import fashion_mnist


# In[2]:


from keras.models import Sequential


# In[3]:


from keras.utils import to_categorical


# In[4]:


from keras.layers import Dense, Flatten


# In[5]:


(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()


# In[6]:


X_train = X_train / 255.0


# In[7]:


X_test = X_test / 255.0


# In[8]:


y_train = to_categorical(y_train, 10)


# In[9]:


y_test = to_categorical(y_test, 10)


# In[10]:


model = Sequential([
    Flatten(input_shape = (28, 28)),
    Dense(128, activation = 'relu'),
    Dense(10, activation = 'softmax')
])


# In[11]:


model.compile(optimizer = 'adam', loss = 'categorical_crossentropy', metrics = ['accuracy'])


# In[12]:


model.fit(X_train, y_train, epochs = 5, batch_size = 32, validation_split = 0.1, verbose = 0)


# In[13]:


loss, acc = model.evaluate(X_test, y_test)


# In[14]:


y_pred = model.predict(X_test)


# In[15]:


y_pred_class = y_pred.argmax(axis = 1)


# In[16]:


y_true_class = y_test.argmax(axis = 1)


# In[17]:


classes = ['Dress', 'Coat', 'Jeans', 'Ankle Boot', 'Trouser', 'T-shirt', 'Pant', 'Shirt', 'Pullover', 'Sneaker']


# In[18]:


for i in range(15) :
    print(f"Actual Fashion Class : {classes[y_true_class[i]]}\tPredicted Fashion Class : {classes[y_pred_class[i]]}")


# In[19]:


y_test[0:20]


# In[20]:


y_pred_class[0:20]


# In[21]:


y_pred[0 : 20]


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




