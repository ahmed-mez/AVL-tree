#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AVL_tree.h"

/* Utility function to get height of the tree
  Return 0 if node is NULL
*/
int height(struct Node *node)
{
  if (!node)
    return 0;
  return node->height;
}

/* Utility function to calculate the maximum of two integers
 */
int max(int a, int b)
{
  return (a > b)? a : b;
}

/* Function to recalculate the node height from its children's heights
*/
void updateHeight(struct Node *node) {
  node->height = max(height(node->left), height(node->right)) + 1;
}

/* Funtion to return the number of nodes in the subtree node
   Return 0 if node is NULL
*/
int nbNode(const struct Node* node)
{
  if (!node)
    return 0;
  else
      return 1 + nbNode(node->left) + nbNode(node->right);
}

/* Function to release all elements of the subtree node including node
   Return NULL
*/
struct Node *release(struct Node *node)
{
  if (node)
  {
    node->left = release(node->left);
    node->right = release(node->right);
    free(node->key); //release the memory allocated to key
    node->key = NULL;
    free(node->value); //release the memory allocated to value
    node->value = NULL;
    free(node);
  }
  return NULL;
}

/* Helper function to create a node with key and value
*/
static struct Node* newNode(const char *key, char *value)
{
  struct Node* node = malloc(sizeof(struct Node));
  assert(node);
  node->key = malloc(strlen(key) + 1);
  assert(node->key);
  strcpy(node->key, key);
  node->value = malloc(strlen(value) + 1);
  assert(node->value);
  strcpy(node->value, value);
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

/* Utility function to right rotate the subtree rooted with z
*/
static struct Node *rightRotate(struct Node *z)
{
  struct Node *y = z->left;
  z->left = y->right;
  y->right = z;
  updateHeight(z);
  updateHeight(y);
  return y;
}

/* Utility function to left rotate the subtree rooted with z
*/
static struct Node *leftRotate(struct Node *z)
{
  struct Node *y = z->right;
  z->right = y->left;
  y->left = z;
  updateHeight(z);
  updateHeight(y);
  return y;
}

/* Recursive function to insert key in subtree rooted with node
   Return the new root of subtree
*/
struct Node* insert(struct Node* node, const char* key, char *value)
{
  if (!node)
    return newNode(key, value);
  else
  {
    if (strcmp(key, node->key) < 0)
      node->left = insert(node->left, key, value);
    else if (strcmp(key, node->key) > 0)
      node->right = insert(node->right, key, value);
    else if (strcmp(key, node->key) == 0)
    {
      node->value = realloc(node->value, strlen(value) + 1);
      assert(node->value);
      strcpy(node->value, value);
      return node;
    }
  }
  updateHeight(node);
  int balance = height(node->left) - height(node->right);
  if (balance < -1 || balance > 1)
  {
    if (balance > 1 && (strcmp(key, node->left->key) < 0))
      return rightRotate(node);
    if (balance < -1 && (strcmp(key, node->right->key) > 0))
      return leftRotate(node);
    if (balance > 1 && (strcmp(key, node->left->key) > 0))
    {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && (strcmp(key, node->right->key) < 0))
    {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

/* Function to search for a node by its key
   Return NULL if node not found
*/
struct Node* searchNode(struct Node *node, const char *key)
{
  if (!node)
    return NULL;
  if (strcmp(key, node->key) < 0)
    return searchNode(node->left, key);
  else if (strcmp(key, node->key) > 0)
    return searchNode(node->right, key);
  else if (strcmp(key, node->key) == 0)
    return node;
  return node;
}

/* Function to get height of key in subtree rooted with node
   Return 0 if key not found
*/
int getKeyHeight(struct Node* node, const char *key)
{
  struct Node* new_node = searchNode(node, key);
  if (new_node)
    return new_node->height;
  return 0;
}

/* Function to get rank of key in subtree rooted with node
   Return -1 if key not found
*/
int getKeyRank(const struct Node* node, const char *key)
{
  int rank = 0;
  while (node)
  {
    if (strcmp(key, node->key) < 0)
      node = node->left;
    else if (strcmp(key, node->key) > 0)
    {
      rank += nbNode(node->left) + 1;
      node = node->right;
    }
    else
      return nbNode(node->left) + rank;
  }
  return -1;
}

/* Fonction to get the value associated to key
   Return NULL if key not found
*/
char *getValue(struct Node *node, const char *key)
{
  struct Node* new_node = searchNode(node, key);
  if (new_node)
    return new_node->value;
  return NULL;
}

/* Function to print postorder traversal of the AVL tree
*/
void postorder(struct Node* node)
{
     if (node == NULL)
        return;
     postorder(node->left);
     postorder(node->right);
     printf("%s ", node->key);
}

/* Function to print inorder traversal of the AVL tree
*/
void inorder(struct Node* node)
{
     if (node == NULL)
          return;
     inorder(node->left);
     printf("%s ", node->key);
     inorder(node->right);
}

/* Function to print preorder traversal of the AVL tree
*/
void preorder(struct Node* node)
{
     if (node == NULL)
          return;
     printf("%s ", node->key);
     preorder(node->left);
     preorder(node->right);
}

int main() {
  struct Node *root = NULL;

  // Constructing an AVL tree
  root = insert(root, "A", "A_value");
  root = insert(root, "B", "B_value");
  root = insert(root, "C", "C_value");
  root = insert(root, "D", "D_value");
  root = insert(root, "G", "G_value");
  root = insert(root, "F", "F_value");
  root = insert(root, "E", "E_value");
  root = insert(root, "H", "H_value");

  // Printing the traversal of AVL tree
  printf("Post order traversal of the constructed AVL tree is :\n");
  postorder(root);
  printf("\n\nIn order traversal of the constructed AVL tree is :\n");
  inorder(root);
  printf("\n\nPre order traversal of the constructed AVL tree is :\n");
  preorder(root);
  printf("\n");

  // Releasing the AVL tree
  root = release(root);

  return 0;
}
