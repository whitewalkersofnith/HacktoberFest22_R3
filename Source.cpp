#include<iostream>
using namespace std;
#define S 20
int map[S][S] = { 0 };
int vis[S][S] = { 0 };
int visD[S][S] = { 0 };
int x_dir[4] = { 1,0,-1,0 };
int y_dir[4] = { 0,1,0,-1 };
int cellCount = 0;
int cluster = 0;
bool isLaserAllowed(int M, int N, int x, int y) {
	return (x >= 0 && y >= 0 && x < M&& y < N&& map[x][y] == 0);
}
void Dfs(int x, int y, int M, int N) {
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int next_x = x + x_dir[i];
		int next_y = y + y_dir[i];
		if (isLaserAllowed(M, N, next_x, next_y) && !vis[next_x][next_y]) {
			Dfs(next_x, next_y, M, N);
		}
	}

}

void reset(int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			
			vis[i][j] = 0;
			visD[i][j] = 0;
		}
	}
}

int countCells(int M, int N) {
	//cout << "--------------------------------------------------\n";
	int cnt = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			//cout << vis[i][j] << "   ";
			if (vis[i][j] == 2 || vis[i][j] == 3) {
				cnt++;
			}
		}
		//cout << endl;
	}
	return cnt;
}
void print(int M, int N) {
	cout << "PRINTING..................\n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << vis[i][j] << "   ";
			
		}
		cout << endl;
	}
	cout << "PRINTING Done..................\n";
}
void spreadLaser(int M, int N, int _i, int _j) {
	int row = _i;
	int col = _j;
	for (int i = row; i < M; i++) {
		if (map[i][col] == 1) {
			break;
		}
		if (vis[i][col] == 0) {
			vis[i][col] = 3;
		}
	}
	for (int i = row; i >=0; i--) {
		if (map[i][col] == 1) {
			break;
		}
		if (vis[i][col] == 0) {
			vis[i][col] = 3;
		}
	}
	for (int j =col; j < N; j++) {
		if (map[row][j] == 1) {
			break;
		}
		if (vis[row][j] == 0) {
			vis[row][j] = 3;
		}
	}
	for (int j = col; j >=0; j--) {
		if (map[row][j] == 1) {
			break;
		}
		if (vis[row][j] == 0) {
			vis[row][j] = 3;
		}
	}
	//print(M, N);
}

void BruteForce(int M, int N) {
	int countc = 0;
		for (int i1 = 0; i1 < M; i1++) {
			for (int j1 = 0; j1 < N; j1++) {
				cout << "chk " << i1 << "  " << j1 << endl;
				if (isLaserAllowed(M, N, i1, j1) && vis[i1][j1] == 0) {
					vis[i1][j1] = 2;
					//cout << "placed 1 " << i1 << "    " << j1 << endl;
					spreadLaser(M, N, i1, j1);
					//print(M, N);
					for (int i2 = 0; i2 < M; i2++) {
						for (int j2 = 0; j2 < N; j2++) {
							if (isLaserAllowed(M, N, i2, j2) && vis[i2][j2] == 0) {
								vis[i2][j2] = 2;
								//cout << "placed 2 " << i2 << "    " << j2 << endl;
								spreadLaser(M, N, i2, j2);
								for (int i3 = 0; i3 < M; i3++) {
									for (int j3 = 0; j3 < N; j3++) {
										//cout << "check   " << i3 << "   " << j3 << "  " << (vis[i3][j3]==0) << endl;
										if (isLaserAllowed(M, N, i3, j3) && vis[i3][j3] == 0) {
											//cout << "3 posl" << endl;
											vis[i3][j3] = 2;
											spreadLaser(M, N, i3, j3);

											//cout << "placed 3 " << i3 << "    " << j3 << endl;
											//print(N, M);
											
											countc = countCells(M, N);
											
											//cout << countc << " " << cellCount << endl;
											
											//
											if (countc > cellCount) {

												cellCount = countc;
												print(M, N);
												//cout << "cord  " << cellCount << " " << i1 << " " << j1 << " " << i2 << "  " << j2 << " " << i3 << " " << j3 << endl;
												int clCount = 0;
												
												for (int l = 0; l < M; l++) {
													for (int m = 0; m < N; m++) {
														//cout << vis[l][m] << "  ";
														if ((vis[l][m] == 0) && (map[l][m] == 0)) {
															Dfs(l, m, M, N);
															clCount++;
														}

													}
													//cout << endl;
												}
												
												cluster = clCount;

												cout << "/////////////////////////////" << endl;
											}
											reset(M, N);
										}
									}
								}
							}
						}
					}
				}

			}
		}
	
}
int main() {
	int t;
	cin >> t;
	for (int test_case = 1; test_case <= t; test_case++) {
		int M, N,x;
		cin >> M >> N;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> x;
				map[i][j] = x;
				vis[i][j] = 0;
				visD[i][j] = 0;
			}
		}
		BruteForce(M, N);
		cout << cellCount << "         " << cluster << endl;

	}
}