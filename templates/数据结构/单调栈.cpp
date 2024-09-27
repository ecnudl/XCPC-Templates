int main()
{
    stack<int> st;
    int n;cin >> n;
    vector<int> ans;
    for(int i = 0;i < n;i++)
    {
        int num;
        cin >> num;
        if(st.empty()) ans.push_back(-1);
        else
        {
            while(!st.empty() && st.top() >= num)st.pop();
            if(st.empty()) ans.push_back(-1);
            else ans.push_back(st.top());
        }
        st.push(num);
    }
    for(auto it : ans) cout << it << ' ';
    return 0;
}