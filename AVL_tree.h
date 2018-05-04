#include <stdlib.h>
#include <assert.h>
#include <string.h>

//node of the AVL tree
struct Node
{
  char *key;
  char *value;
  struct Node *left;
  struct Node *right;
  int height;
};

int getKeyHeight(struct Node* node, const char *key);

int getKeyRank(const struct Node* node, const char *key);

int nbNode(const struct Node* node);

struct Node* insert(struct Node* node, const char* key, char *value);

struct Node *release(struct Node *node);

char *getValue(struct Node *node, const char *key);
