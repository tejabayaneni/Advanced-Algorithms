using namespace std;
template<class K, class T>
struct node {
    K key;
    T info;
    node<K, T>* left;
    node<K, T>* right;
    node<K, T>* parent;
    bool black;
};

struct WordsFamily {
    int freq;
    set<string> family;
};

template<class K, class T>
class RBTreeMap
        {
        public:
            RBTreeMap();
             void addNode(K newKey, WordsFamily newInfo);
            // Adds newInfo to the tree using newKey as a key
            void remove(K newKey);
            // Removes node that contains newKey
            T getInfo(K key);
            /* Returns element and associated key*/
            node<K,T>* TreeSearch(string stuff);
            void setInfo(K key);
            set<string> bigFamily();
            node<K,T>* GetRoot();
						int length;

        private:
            node<K, T>* root;
            int length1;

        };
