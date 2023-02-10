#include<iostream>

using namespace std;

int main (int argc, char **argv) {
	//cout << "start do with n = " << argv[1] << endl;
	int G = 300000000;
	int q = 10000007;
	int n = atoi(argv[1]);
	//посчитаем сумму чисел фибоначи, которые стоят на позициях n,2n,3n...kn<=G, mod = q
	int a1 = 1;
	int a2 = 1;
	int ans = 0;
	if (n == 1){
		ans+=2;
	}
	if (n == 2){
		ans+=1;
	}

	for (int i = 3; i <= G; i++){
		int a12 = a2;
		a2 = a1 + a2;
		a1 = a12;
		if (i%n == 0){
			ans+=a2;
		}
		ans = ans%q;
	}
	//cout << "result:" << ans << endl;
 	//cout << "end do with n = " << n << endl;

	return 0;
}