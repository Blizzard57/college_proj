# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
import gif
import seaborn as sns; sns.set()
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math
from mpl_toolkits.mplot3d import Axes3D


# %%
# Function to plot our input data for classification tasks.
def plot_2D_input_datapoints(X_inp, y_inp):

  """Method to plot 2D datapoints for classification tasks.

  Parameters
  ------------

  X_inp: ndarray (num_examples(rows) vs num_features(columns))
    Input data which would be plotted.

  Y_inp: ndarray (num_examples(rows) vs num_outputs(columns))
    Corresponding labels of X_inp
  """
  sns.set();
  
  X_inp = X_inp[:, :2]
  inp_data = np.hstack((X_inp, y_inp.reshape(-1, 1)))
  df = pd.DataFrame(data=inp_data, columns=["$X_0$", "$X_1$", "$y$"])
  sns.scatterplot(x="$X_0$", y="$X_1$", hue="$y$", legend='full',  data=df)
  plt.title('Input data')
  plt.legend(loc='lower right');


# %%
# Sourced from https://github.com/eriklindernoren/ML-From-Scratch
# Method to normalize the data
def normalize(X, axis=-1, order=2):
    """ Normalize the dataset X """
    l2 = np.atleast_1d(np.linalg.norm(X, order, axis))
    l2[l2 == 0] = 1
    return X / np.expand_dims(l2, axis)


# %%
# Defining our sigmoid activation function
def sigmoid(vec_w_x, predict='no'):

  """ Sigmoid activation for binary classification.

  Parameters
  ------------

  vec_w_x: ndarray
    Weighted inputs
   
  predict: str ('yes' or 'no')
    'no' corresponds to training
    'yes' corresponds to prediction
  """

  pred_prob = (1 / (1 + np.exp(-1 * vec_w_x)))
  
  if predict == 'yes':
    pred_prob[pred_prob >= 0.5] = 1
    pred_prob[pred_prob < 0.5] = 0

  return pred_prob


# %%
# Defining our softmax function for classification
def softmax(X_input_set, vec_w_x, predict='no'):

  """ softmax activation for multiclass classification.

  Parameters
  ------------

  vec_w_x: ndarray
    Weighted inputs
  
  X_input_set: ndarray
    Input dataset whose examples have to be classified
  
  predict: str ('yes' or 'no')
    'no' corresponds to training
    'yes' corresponds to prediction
  """

  num_datapoints = np.shape(X_input_set)[0]

  # Computing predicted probabilites using softmax function
  exp_units = np.exp(vec_w_x)
  summation_exp_units = np.sum(exp_units, axis=-1, keepdims=True)
  pred_prob = exp_units/summation_exp_units

  # Predicting classes
  if predict == 'yes':
    maxvals = np.amax(pred_prob, axis=1)
    for i in range(num_datapoints):
      idx = np.argwhere(pred_prob == maxvals[i])[0]
      pred_prob[idx[0], idx[1]] = 1

    non_maxvals_idxs = np.argwhere(pred_prob != 1)
    pred_prob[non_maxvals_idxs[:, 0], non_maxvals_idxs[:, 1]] = 0

  return pred_prob


# %%
# Defining signum activation function
def signum(vec_w_x):
  """ signum activation for perceptron

  Parameters
  ------------
  vec_w_x: ndarray
    Weighted inputs
  """

  vec_w_x[vec_w_x >= 0] = 1
  vec_w_x[vec_w_x < 0] = -1
  return vec_w_x


# %%
# multi-class signum
def multi_class_signum(vec_w_x):
  """ Multiclass signum activation.

  Parameters
  ------------
  vec_w_x: ndarray
    Weighted inputs
  """

  flag = np.all(vec_w_x == 0)

  if flag:
    return vec_w_x

  else:
    num_examples, num_outputs = np.shape(vec_w_x)
    range_examples = np.array(range(0, num_examples))

    zero_idxs = np.argwhere(np.all(vec_w_x == 0, axis=1))
    non_zero_examples = np.delete(range_examples, zero_idxs[:, 0])
      
    signum_vec_w_x = vec_w_x[non_zero_examples]
    maxvals = np.amax(signum_vec_w_x, axis=1)
    
    for i in range(num_examples):
      idx = np.argwhere(signum_vec_w_x == maxvals[i])[0]
      signum_vec_w_x[idx[0], idx[1]] = 1

    non_maxvals_idxs = np.argwhere(signum_vec_w_x != 1)
    signum_vec_w_x[non_maxvals_idxs[:, 0], non_maxvals_idxs[:, 1]] = -1
    vec_w_x[non_zero_examples] = signum_vec_w_x

    return vec_w_x


# %%
# Evaluation for train, val, and test set.
def get_accuracy(y_predicted, Y_input_set, num_datapoints):
  miscls_points = np.argwhere(np.any(y_predicted != Y_input_set, axis=1))
  miscls_points = np.unique(miscls_points)
  accuracy = (1-len(miscls_points)/num_datapoints)*100
  return accuracy

def get_prediction(X_input_set, Y_input_set, weights, get_acc=False, model_type='perceptron', predict='no'):

  if len(Y_input_set) != 0:
    num_datapoints, num_categories = np.shape(Y_input_set)

  vec_w_transpose_x = np.dot(X_input_set, weights)

  if num_categories > 1: # Multi-class
    if model_type == 'perceptron':
      y_pred_out = multi_class_signum(vec_w_transpose_x)
    elif model_type == 'logreg':
      y_pred_out = softmax(X_input_set, vec_w_transpose_x, predict=predict)

  else: # Binary class
    if model_type == 'perceptron' or model_type == 'LinearDA':
      y_pred_out = signum(vec_w_transpose_x)
    elif model_type == 'logreg':
      y_pred_out = sigmoid(vec_w_transpose_x, predict=predict)

  # Both prediction and evaluation
  if get_acc:
    cls_acc = get_accuracy(y_pred_out, Y_input_set, num_datapoints)
    return cls_acc, y_pred_out
  
  # Only prediction
  return y_pred_out


# %%
# Method to generate gifs of decision boundary
def generate_gifs(X, y, trained_weights, dataset_type, path='/path/filename.gif', bias='on', class_label_01_form='off', model_type='perceptron', predict='no'):
  if dataset_type == 'train':
    frames = []
    for i in range(len(trained_weights)):
      frame = plot_decision_boundary(X, y, trained_weights, i, dataset_type=dataset_type, bias=bias, 
                                     class_label_01_form=class_label_01_form, model_type=model_type, predict=predict)
      frames.append(frame)
    gif.save(frames, path, duration=500)
  
  print('Gif/image generated')


# %%
@gif.frame
def plot_decision_boundary(X_input, Y_input, weights, i=0, dataset_type='test', bias='on', class_label_01_form='off', model_type='perceptron', predict='no'):

  """ Plotting decision boundary for train/test set. This method can
  also be used to plot a single decision boundary instead of a gif.

  Parameters
  -----------

  X_input: ndarray (num_examples(rows) vs num_features(columns))
    Input data which you would like to plot

  Y_input: ndarray (num_examples(rows) vs num_outputs(columns))
    Class labels

  weights: ndarray (num_features(rows) vs num_outputs(columns))
    Trained weights

  dataset_type: str
    Depending on the dataset_type, different plot/gifs will be generated.

  bias: str
    This is used to portray the effect of bias for the perceptron model

  class_label_01_form: str
    Signum activation results output labels in the form {-1, +1}.
    If class_label_01_form is True, {-1, +1} will change to {0, 1}

  model_type: str
    Depending on the model_type, different plot/gifs will be generated.

  predict: str
    If predict is true, thresholding in activation function will be done.
  """

  plt.figure(figsize=(8,8));
  sns.set();

  h = 0.008

  input_data = X_input[:,:2]
  x0_min, x0_max = input_data[:, 0].min() - 1, input_data[:, 0].max() + 1
  x1_min, x1_max = input_data[:, 1].min() - 1, input_data[:, 1].max() + 1
  xx0, xx1 = np.mgrid[x0_min:x0_max:h, x1_min:x1_max:h]

  # making prediction over the datapoint space
  xx0_xx1 = np.c_[xx0.ravel(), xx1.ravel()]
  if bias == 'on':
    b_ones = np.ones((len(xx0_xx1), 1))
    xx0_xx1 = np.hstack((xx0_xx1, b_ones))

  # Getting prediction over the datapoint space
  if dataset_type == 'train':
    #Z = get_prediction(xx0_xx1, np.array([]), weights[i], get_acc=False)
    Z = np.dot(xx0_xx1, weights[i])
    Z = Z.reshape(xx0.shape)
    y_pred = get_prediction(X_input, Y_input, weights[i], get_acc=False, model_type=model_type, predict=predict)

  elif dataset_type == 'test':
    #Z = get_prediction(xx0_xx1, np.array([]), weights, get_acc=False)
    Z = np.dot(xx0_xx1, weights)
    Z = Z.reshape(xx0.shape)
    y_pred = get_prediction(X_input, Y_input, weights, get_acc=False, model_type=model_type, predict=predict)

  # Converting labels from {-1, 1} to {0, 1}
  if class_label_01_form == 'on':
    if np.shape(Y_input)[1] > 1:
      neg_one_class_idxs = np.argwhere(y_pred == -1)
      y_pred[neg_one_class_idxs[:, 0], neg_one_class_idxs[:, 1]] = 0
      y_pred = y_pred.reshape((-1, np.shape(Y_input)[1]))
    else:
      neg_one_class_idxs = np.argwhere(y_pred == -1)[:, 0]
      y_pred[neg_one_class_idxs] = 0
      y_pred = y_pred.reshape((-1, 1))

  # Getting misclassfied points on train/val/test set
  miscls_points = np.unique(np.argwhere(y_pred != Y_input)[:, 0])
  
  # Put the result into a color plot
  plt.contour(xx0, xx1, Z, levels=[0], cmap='gray')

  pred_data = np.hstack((X_input[:,:2], y_pred))
  df = pd.DataFrame(data=pred_data, columns=["$X_0$", "$X_1$", "Y_"+dataset_type+"_pred"])
  sns.scatterplot(x="$X_0$", y="$X_1$", hue="Y_"+dataset_type+"_pred", legend='full', data=df)
  plt.scatter(X_input[miscls_points, 0], X_input[miscls_points, 1], s=150, cmap="Greens", marker='x')
  plt.title(dataset_type+' data')
  plt.tight_layout();
  plt.legend(loc='lower right');


# %%
# Mean squared error
def mse_error(X_train, Y_train, THETA):
  Y_PRED = np.dot(X_train, THETA)
  m_sq_error = np.mean(0.5 * (Y_train - Y_PRED)**2)
  return m_sq_error


# %%
@gif.frame
def plot_convex_loss_and_predict_line(training_mse, weights, X_train, Y_train, Y_train_pred, i):

  """ Method to plot Gradient Descent.

  Parameters
  -----------

  training_mse: ndarray
    List of training errors used to create decision boundary for every epoch/iteration.
  
  weights: ndarray
    List of trained weights. This is used to create decision boundary for every epoch/iteration
    and to see how the decision boundary changes.

  X_train: ndarray (num_examples(rows) vs num_features(columns))
    Input data which you would like to plot

  Y_train: ndarray (num_examples(rows) vs num_outputs(columns))
    Class labels

  Y_train_pred: ndarray (num_examples(rows) vs num_outputs(columns))
    Class labels
  """

  fig = plt.figure(figsize=(15,10))
  cmap = plt.get_cmap('cividis')
  ax = fig.add_subplot(2, 1, 1, projection='3d')
  
  sns.set();
  
  weights = np.array(weights)
  training_mse = np.array(training_mse) 

  weight_b_grid = np.linspace(weights[-1][0] - 20, weights[-1][0] + 20, 20) #intercept
  weight_m_grid = np.linspace(weights[-1][1] - 40, weights[-1][1] + 40, 40) #slope

  # Generating convex loss surfaces 
  B, M = np.meshgrid(weight_b_grid, weight_m_grid)
  Y_train = Y_train.reshape(-1,)
  zs = np.array([mse_error(X_train, Y_train, theta)
                for theta in zip(np.ravel(B), np.ravel(M))])
  Z = zs.reshape(M.shape)

  ax.plot_surface(B, M, Z, rstride=1, cstride=1, color='blue', alpha=0.25)
  ax.plot(weights[:i+1, 0], weights[:i+1, 1], training_mse[:i+1], markerfacecolor='r', markeredgecolor='r', marker='*', markersize=10, color='black')

  # Plotting loss vs prediction
  ax.set_title("Loss vs weights")
  ax.set_xlabel('weight(b)', labelpad=20)
  ax.set_ylabel('weight(m)', labelpad=20)
  ax.set_zlabel('Training loss', labelpad=10)
  ax.view_init(elev=10, azim=25)

  ax = fig.add_subplot(2, 1, 2)
  ax.scatter(X_train[:, 1], Y_train, color=cmap(1), s=10)
  ax.plot(X_train[:, 1], Y_train_pred[i], color='red', linewidth=0.2, label="Training-Prediction")

  ax.set_title("Linear Regression")
  ax.set_xlabel('Input (X_train)')
  ax.set_ylabel('Y_train')
  plt.tight_layout()


