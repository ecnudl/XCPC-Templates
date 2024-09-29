    auto get = [&] (int x) {
        vector<AI<2> > tmp;
        for(int i = 2;i <= x / i;i++) {
            if(x % i == 0) {
                int j = 0;
                while(x % i == 0) {
                    x /= i;
                    j++;
                }
                tmp.pb({i, j});
            }
        }
        if(x > 1) tmp.pb({x, 1});
        return tmp;
    };