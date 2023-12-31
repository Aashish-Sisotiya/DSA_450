//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node
{
    int data;
    Node *left;
    Node *right;
};

// Utility function to create a new Tree Node
Node *newNode(int val)
{
    Node *temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

vector<int> diagonal(Node *root);

// Function to Build Tree
Node *buildTree(string str)
{
    // Corner Case
    if (str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;)
        ip.push_back(str);

    // Create the root of the tree
    Node *root = newNode(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size())
    {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N")
        {

            // Create the left child for the current node
            currNode->left = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size())
            break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N")
        {

            // Create the right child for the current node
            currNode->right = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}

int main()
{
    int t;
    string tc;
    getline(cin, tc);
    t = stoi(tc);
    while (t--)
    {
        string s, ch;
        getline(cin, s);
        Node *root = buildTree(s);

        vector<int> diagonalNode = diagonal(root);
        for (int i = 0; i < diagonalNode.size(); i++)
            cout << diagonalNode[i] << " ";
        cout << endl;
    }
    return 0;
}

// } Driver Code Ends

/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

void diagonalTraversal(Node *root, vector<int> &ans)
{
    if (!root)
        return;

    stack<Node *> st;  // instead of using a stack use a pointer node curr and move it to its right , and if curr points to null then curr= q.front()
    queue<Node *> q;

    st.push(root);
    while (!st.empty() || !q.empty())
    {

        if (!st.empty())
        {
            Node *topNode = st.top();
            st.pop();
            ans.push_back(topNode->data);
            if (topNode->right)
                st.push(topNode->right);
            if (topNode->left)
                q.push(topNode->left);
        }
        if (st.empty() && !q.empty())
        {
            st.push(q.front());
            q.pop();
        }
    }
}
void diagonalPrintUtil(Node *root, int d,
                       map<int, vector<int>> &diagonalPrint)
{
    // Base case
    if (!root)
        return;

    // Store all nodes of same
    // line together as a vector
    diagonalPrint[d].push_back(root->data);

    // Increase the vertical
    // distance if left child
    diagonalPrintUtil(root->left,
                      d + 1, diagonalPrint);

    // Vertical distance remains
    // same for right child
    diagonalPrintUtil(root->right,
                      d, diagonalPrint);
}
vector<int> diagonal(Node *root)
{
    // your code here
    vector<int> ans;
    if (root == NULL)
        return ans;
    // diagonalTraversal(root,ans);
    map<int, vector<int>> diagonalPrint;
    diagonalPrintUtil(root, 0, diagonalPrint);

    for (auto it : diagonalPrint)
    {
        vector<int> v = it.second;
        for (auto it : v)
        {
            ans.push_back(it);
        }
    }
    return ans;
}