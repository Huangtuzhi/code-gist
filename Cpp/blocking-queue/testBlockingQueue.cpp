#include "./concurrence/BlockingQueue.hpp"
#include <iostream>
#include <string>
using namespace GistUtil;
using namespace std;

int main()
{
	BlockingQueue<string> testQueue(1000);
	
	for (int i=0; i<1005; i++) {
		// 等待 2S 超时后不再等待
		int iRet = testQueue.TimedPush("titus_" + to_string(i), 2000);
		cout << iRet << endl;
	}

	for (int i=0; i<1005; i++) {
		string val;
		// 等待 4S 超时后不再等待，继续后面的逻辑
		int iRet = testQueue.TimedPop(&val, 4000);
		cout << "ret=" << iRet << "|val=" << val << endl; 
	}

	return 0;
}