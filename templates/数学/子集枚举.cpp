//用于动态规划或者某些需要状压枚举子集的情况，复杂度是3^n
int up = (1 << n);
for(int i = 0;i < up;i++) {
	for(int j = i;j >= 0;j = (j - 1) & i) {
		if(j == 0) break; //是否需要枚举到0再自行判断
	}
}