struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;

SearchTree MakeEmpty(SearchTree t);
Position Find(ElementType x, SearchTree t);
Position FindMax(SearchTree t);
Position FindMin(SearchTree t);
SearchTree Insert(ElementType x, SearchTree t);
SearchTree Delete(ElementType x, SearchTree t);
ElementType Retrieve(Position p);