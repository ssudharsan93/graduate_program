import numpy as np


def fc_forward(x, w, b):
    """
    Computes the forward pass for a fully-connected layer.

    The input x has shape (N, Din) and contains a minibatch of N
    examples, where each example x[i] has shape (Din,).

    Inputs:
    - x: A numpy array of shape (N, Din) giving input data
    - w: A numpy array of shape (Din, Dout) giving weights
    - b: A numpy array of shape (Dout,) giving biases

    Returns a tuple of:
    - out: output, of shape (N, Dout)
    - cache: (x, w, b)
    """
    out = None
    ###########################################################################
    # TODO: Implement the forward pass. Store the result in out.              #
    ###########################################################################
    #print("x:", end='')
    #print(x.shape)
    #print("w:", end='')
    #print(w.shape)
    out = x @ w
    out = out + b
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = (x, w, b)
    return out, cache


def fc_backward(grad_out, cache):
    """
    Computes the backward pass for a fully-connected layer.

    Inputs:
    - grad_out: Numpy array of shape (N, Dout) giving upstream gradients
    - cache: Tuple of:
      - x: A numpy array of shape (N, Din) giving input data
      - w: A numpy array of shape (Din, Dout) giving weights
      - b: A numpy array of shape (Dout,) giving biases

    Returns a tuple of downstream gradients:
    - grad_x: A numpy array of shape (N, Din) of gradient with respect to x
    - grad_w: A numpy array of shape (Din, Dout) of gradient with respect to w
    - grad_b: A numpy array of shape (Dout,) of gradient with respect to b
    """
    x, w, b = cache
    grad_x, grad_w, grad_b = None, None, None
    ###########################################################################
    # TODO: Implement the backward pass for the fully-connected layer         #
    ###########################################################################
    N, Dw = grad_out.shape
    grad_x = grad_out @ w.transpose()
    grad_w = x.transpose() @ grad_out 
    grad_b = np.matrix(np.ones(N)) @ np.matrix(grad_out)
    grad_b = np.asarray(grad_b)
    grad_b = np.resize(grad_b, b.shape)

    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return grad_x, grad_w, grad_b


def relu_forward(x):
    """
    Computes the forward pass for the Rectified Linear Unit (ReLU) nonlinearity

    Input:
    - x: A numpy array of inputs, of any shape

    Returns a tuple of:
    - out: A numpy array of outputs, of the same shape as x
    - cache: x
    """
    out = None
    ###########################################################################
    # TODO: Implement the ReLU forward pass.                                  #
    ###########################################################################
    relu_func = np.vectorize(lambda x: float(max(x, 0)), otypes=[float])
    out = relu_func(x)
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    cache = x
    return out, cache


def relu_backward(grad_out, cache):
    """
    Computes the backward pass for a Rectified Linear Unit (ReLU) nonlinearity

    Input:
    - grad_out: Upstream derivatives, of any shape
    - cache: Input x, of same shape as dout

    Returns:
    - grad_x: Gradient with respect to x
    """
    grad_x, x = None, cache
    ###########################################################################
    # TODO: Implement the ReLU backward pass.                                 #
    ###########################################################################
    relu_deriv_func = np.vectorize(lambda x: float(int(x > 0)), otypes=[float])
    grad_x = grad_out * relu_deriv_func(x)
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return grad_x


def l2_loss(x, y):
    """
    Computes the loss and gradient of L2 loss.

    loss = 0.5 * sum_i (x_i - y_i)**2 / N

    Inputs:
    - x: Input data, of shape (N, D)
    - y: Output data, of shape (N, D)

    Returns a tuple of:
    - loss: Scalar giving the loss
    - grad_x: Gradient of the loss with respect to x
    """
    N = x.shape[0]
    diff = x - y
    loss = 0.5 * np.sum(diff * diff) / N
    grad_x = diff / N
    return loss, grad_x


def softmax_loss(x, y):
    """
    Computes the loss and gradient for softmax (cross-entropy) loss function.

    Inputs:
    - x: Numpy array of shape (N, C) giving predicted class scores, where
      x[i, c] gives the predicted score for class c on input sample i
    - y: Numpy array of shape (N,) giving ground-truth labels, where
      y[i] = c means that input sample i has ground truth label c, where
      0 <= c < C.

    Returns a tuple of:
    - loss: Scalar giving the loss
    - grad_x: Numpy array of shape (N, C) giving the gradient of the loss with
      with respect to x
    """
    loss, grad_x = None, None
    ###########################################################################
    # TODO: Implement softmax loss                                            #
    ###########################################################################
    N = x.shape[0]
    M_i = np.amax(x, axis=1)
    z_i_c = np.asarray(np.matrix(x) - np.matrix(M_i).T)
    #print(z_i)
    exp_z_i_c = np.exp(z_i_c)
    #print(exp_z_i)
    exp_sum_z_i_c = np.sum( exp_z_i_c, axis=1 )
    exp_sum_z_i_c = np.resize(exp_sum_z_i_c, (N,1))
    #print(exp_sum_z_i)
    p_i_c = exp_z_i_c / exp_sum_z_i_c
    #print(p_i_c)
    #print(y)
    pi_yi = p_i_c[np.arange(N), y]
    #print(pi_yi)
    loss = ( -1.0 / float(N) ) * np.sum(np.log(pi_yi))
    #print(loss)
    delta_y_i_c = np.zeros(p_i_c.shape)
    delta_y_i_c[np.arange(N), y] = 1
    #print(delta_y_i_c)
    grad_x = ( ( p_i_c - delta_y_i_c ) / float(N) )
    #print(grad_x)

    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return loss, grad_x


def l2_regularization(w, reg):
    """
    Computes loss and gradient for L2 regularization of a weight matrix:

    loss = (reg / 2) * sum_i w_i^2

    Where the sum ranges over all elements of w.

    Inputs:
    - w: Numpy array of any shape
    - reg: float giving the regularization strength

    Returns:
    """
    loss, grad_w = None, None
    ###########################################################################
    # TODO: Implement L2 regularization.                                      #
    ###########################################################################
    loss = float( reg / 2 ) * np.sum(w * w)
    grad_w = reg * w
    ###########################################################################
    #                             END OF YOUR CODE                            #
    ###########################################################################
    return loss, grad_w
