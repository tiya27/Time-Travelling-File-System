#include<bits/stdc++.h>
using namespace std;
using timestampint = long long;
//Time-Travelling File system

// unordered_map<string, File*> files; 
// Heap RecentHeap;  
// Heap BiggestHeap; 

//only treeNode - version representation
//Stores ID, content, snapshot msg, timestamps, Parent pointer, children list
struct TreeNode{
    int id;
    string content;
    string msg;
    timestampint created_ts;
    timestampint ss_ts;
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode(int id, const string& content = "" ){
        this -> id = id;
        this -> content = content;
        msg = "";
        created_ts = time(nullptr);
        ss_ts = 0;
        parent = nullptr;
    }

    bool check_ss() const {
        return ss_ts != 0;
    }

    ~TreeNode(){
    for (auto child : children){
        delete child;
    }
}
};

//implementing inthashmap
struct IntHashMap {
    struct data{
        int key;
        TreeNode* val;
        bool occupied;
        data() : key(0), val(nullptr), occupied(false) {}
    };
    data*entry;
    int data_count;
    int done_count;
    IntHashMap(int cap){
        data_count = cap;
        done_count = 0;
        entry = new data[data_count];
    }
    ~IntHashMap(){
        delete[] entry;
    }
    int hash(int key) const {
        int k = key % data_count ;
        if (k < 0) k += data_count;
        return k;
        
    }

   

    // void put(int key, TreeNode* value) {
    //     int idx = hash(key);
    //     int count = 0;
    //     while (entry[idx].occupied && count < data_count) {
    //         if (entry[idx].key == key) {
    //             entry[idx].val = value; 
    //             return;
    //         }
    //         idx = (idx * 2 + 1) % data_count; 
    //         count++;
    //     }
    //     if (count == data_count) return; 

    //     entry[idx].key = key;
    //     entry[idx].val = value;
    //     entry[idx].occupied = true;
    //     done_count++;
    // }
    
    void put(int key, TreeNode* value) {
        if (done_count >= data_count) return; 
        int idx = hash(key);
        while (entry[idx].occupied && entry[idx].key != key) {
            idx = (idx + 1) % data_count;
        }
        if (!entry[idx].occupied){
            done_count++;
        }
        entry[idx].key = key;
        entry[idx].val = value;
        entry[idx].occupied = true;
    }
    TreeNode* getNode(int key) const {
        int idx = hash(key);
        int start = idx;
        while (entry[idx].occupied) {
            if (entry[idx].key == key){
                return entry[idx].val;
            } 
            idx = (idx + 1) % data_count;
            if (idx == start){
                break;
            }
        }
        return nullptr;
    }
    bool contains(int key) const {
        return getNode(key) != nullptr;
    }
};

//implement strhashmap
struct StrHashMap {
    struct data{
        string key;
        TreeNode* val;
        bool occupied;
        data() : key(""), val(nullptr), occupied(false) {}
    };
    data * entry;
    int data_count;
    int done_count;
    StrHashMap(int cap){
        data_count = cap;
        done_count = 0;
        entry = new data[data_count];
    }
    ~StrHashMap(){
        delete[] entry;
    }
    int hash(const string& s) const {
    int val = 0;
    for (char c : s) {
        val += c; 
    }
    int index = val % data_count;
    if (index < 0) index += data_count;
    return index;
}
    void put(const string&key, TreeNode* value) {
        if (done_count >= data_count) return; 
        int idx = hash(key);
        while (entry[idx].occupied && entry[idx].key != key) {
            idx = (idx + 1) % data_count;
        }
        if (!entry[idx].occupied){
            done_count++;
        }
        entry[idx].key = key;
        entry[idx].val = value;
        entry[idx].occupied = true;
    }
    TreeNode* getNode(const string&key) const {
        int idx = hash(key);
        int start = idx;

        while (entry[idx].occupied) {
            if (entry[idx].key == key){
                return entry[idx].val;
            } 
            idx = (idx + 1) % data_count;
            if (idx == start){
                break;
            }
        }
        return nullptr;
    }
    bool contains(const string&key) const {
        return getNode(key) != nullptr;
    }
};


//implement heap
class Heap {
public:
    struct Node {
        long long key;  
        string filename;    
    };
    vector<Node> array;
    void heapify(int i) {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        int size = array.size();
        if (left < size && array[left].key > array[largest].key) {
            largest = left;
        }
        if (right < size && array[right].key > array[largest].key) {
            largest = right;
        }
        if (largest != i) {
            swap(array[i], array[largest]);
            heapify(largest);
        }
    }
public:
    Heap() = default;
    bool empty() const { return array.empty(); }
    void insert(long long key, const string& filename) {
        array.push_back({key, filename});
        int i = int(array.size()) - 1;
        while (i > 0 && array[(i-1)/2].key < array[i].key) {
            swap(array[i], array[(i-1)/2]);
            i = (i-1)/2;
        }
    }
    Node getmax() {
        if (array.empty()) return {LLONG_MIN, ""};
        if (array.size() == 1) {
            Node root = array.back();
            array.pop_back();
            return root;
        }
        Node root = array[0];
        array[0] = array.back();
        array.pop_back();
        heapify(0);
        return root;
    }
};

struct File;
extern unordered_map<string, File*> files;
extern Heap RecentHeap;
extern Heap BiggestHeap;


//File - manages all versions
//contains - implementataion of Tree, HashMap, core file operations
struct File {
    string name;
    TreeNode* root;
    TreeNode* active_version;
    int total_versions;
    int next_vers_id;
    timestampint last_modified;
    //map<int, TreeNode*> version_map;
    IntHashMap version_map;

    File(const string& name) : version_map(10007){ 
        // size required since the hashmap allocates a fixed size array internally, no dynamic resizing 
        this -> name = name;
        root = new TreeNode(0, "");
        root -> msg = "root";
        root -> ss_ts = time(nullptr);
        active_version = root;
        next_vers_id = 1;
        total_versions = 1;
        last_modified = time(nullptr);
        version_map.put(0, root);
       
    }

    //core function implemenatations
    void read() {
        cout << active_version -> content << "\n";
    }

    void insert(const string& addcontent) {
        last_modified = time(nullptr);
        if(!active_version->check_ss()){
            active_version-> content += addcontent;
            active_version->created_ts = last_modified;

        }
        else{
            //new child node
            TreeNode* child = new TreeNode(next_vers_id++, active_version-> content + addcontent);
            child -> parent = active_version;
            active_version-> children.push_back(child);
            active_version = child;
            total_versions++;
            version_map.put(child ->id, child);
        }

        RecentHeap.insert(last_modified, name);
        BiggestHeap.insert(total_versions, name);

    }

    //replace the existing content
    void update(const string& newcontent){
        last_modified = time(nullptr);
        if(!active_version->check_ss()){
            //active_version->content += newcontent;
            active_version-> content = newcontent;
            active_version->created_ts = last_modified;

        }
        else{
            //creates a new child node
            TreeNode* child = new TreeNode(next_vers_id++, newcontent);
            child -> parent = active_version;
            active_version-> children.push_back(child);
            active_version = child;
            total_versions++;
            version_map.put(child ->id, child);

        }

        RecentHeap.insert(last_modified, name);
        BiggestHeap.insert(total_versions, name);
        
    }

    //current version - msg + snapshot timestamp
    void snapshot(const string& message){
        active_version-> ss_ts = time(nullptr);
        active_version -> msg = message;

        RecentHeap.insert(last_modified, name);
        BiggestHeap.insert(total_versions, name);
    }

    //rolling back one version, to parent
    void rollback_parent(){
        if(active_version-> parent != nullptr){
            active_version = active_version-> parent;
            last_modified = time(nullptr);
            cout << "Rollback done, active version:" << active_version-> id << "\n";

        }
        else{
            cout << "At root version, cannot rollback. \n";
        }

        RecentHeap.insert(last_modified, name);
        BiggestHeap.insert(total_versions, name);
    }

    void rollback_to(int version_id){
        //after hashmap implementation
        TreeNode * vers = version_map.getNode(version_id);
        if(vers != nullptr){
            active_version= vers;
            last_modified = time(nullptr);
            cout << "Rollback to version:" << version_id << "\n";
        }
        else{
            cout << "version" << version_id << "not found. \n";
        }

        RecentHeap.insert(last_modified, name);
        BiggestHeap.insert(total_versions, name);
    }

    void history() const {
        vector<TreeNode*> path;
        TreeNode* ver = active_version;
        while( ver != nullptr){
            path.push_back(ver);
            ver = ver-> parent;
        }
        reverse(path.begin(), path.end());
        cout << "File History :" << name << "\n";
        for( auto node : path){
            cout << "version" << node-> id;
            if ( node-> check_ss()){
                cout << "[Snapshot]";
                if (!node-> msg.empty()){
                    cout << " - " << node-> msg;
                }
            }   
            cout << "\n";
        }
    }

    ~File(){
        delete root;
    }
};

unordered_map<string, File*> files; 
Heap RecentHeap;  
Heap BiggestHeap; 

//int main
//int main(int argc, char** argv)

int main() {
    // cout << "Hello" << endl;

    // TreeNode* root = new TreeNode(0, "");
    // cout << "version" << root->id << "content:" << root->content << "\n";
    // return 0;

    string line;
    while(getline(cin, line)){
        if(line == "EXIT"){
            break;
        }
        stringstream ss(line);
        string word;
        ss >> word;

        if(word == "CREATE"){
            string filename;
            ss>> filename;
            if (files.count(filename)){
                cout << "File exists. \n";
            }
            else{
                files[filename] = new File(filename);
                cout << "File Created. \n";
            }
        }

        else if(word == "INSERT"){
            string filename; 
            ss>> filename;
            string content;
            getline(ss, content);
            if(!content.empty() && content[0] == ' '){
                content.erase(0,1);
            files[filename] -> insert(content);
            cout << "OK.\n";
            }
        }

        else if(word == "UPDATE"){
            string filename; 
            ss>> filename;
            string content;
            getline(ss, content);
            if(!content.empty() && content[0] == ' '){
                content.erase(0,1);
            files[filename] -> update(content);
            cout << "OK.\n";
            }
        }

        else if(word == "READ"){
            string filename;
            ss>> filename;
            if (files.count(filename)){
                files[filename] -> read();
            }
            else {
                cout << "Error: File '" << filename << "' not found.\n";
            }
        }

        else if(word == "SNAPSHOT"){
            string filename; 
            ss>> filename;
            string content;
            getline(ss, content);
            if(!content.empty() && content[0] == ' '){
                content.erase(0,1);
            files[filename] -> snapshot(content);
            cout << "OK.\n";
            }
        }

        else if(word == "ROLLBACK"){
            string filename;
            ss>> filename;
            if(files.count(filename)){
                int vers;
                if(ss>> vers){
                    files[filename] -> rollback_to(vers);
                }
                else{
                    files[filename] -> rollback_parent();
                }
            }
            else{
                cout << "File not Found. \n";
            }
        }

        else if(word == "HISTORY"){
            string filename;
            ss>> filename;
            if (files.count(filename)){
                files[filename] -> history();
            }
            else {
                cout << "Error: File '" << filename << "' not found.\n";
            }
        }
            
        else if (word == "RECENT"){
            int num; 
            ss >> num;
            cout << "Top " << num << " most recently modified files:\n";
            Heap temp = RecentHeap;
            for (int i = 0; i < num && !temp.empty(); i++) {
                auto node = temp.getmax();
                cout << node.filename << "\n";
            }
        }

        else if (word == "BIGGEST"){
            int num; 
            ss >> num;
            cout << "Top " << num << " files with the most versions:\n";
            Heap temp = BiggestHeap;
            for (int i = 0; i < num && !temp.empty(); i++) {
                auto node = temp.getmax();
                cout << node.filename << "\n";
            }
        }
    }
    for (auto &p : files) {
    delete p.second;
    }
    files.clear();
    return 0;
}

// //compiler
// #ifdef _WIN32
// #include <windows.h>
// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//             LPSTR lpCmdLine, int nCmdShow) {
//     return main(0, nullptr);
// }
// #endif