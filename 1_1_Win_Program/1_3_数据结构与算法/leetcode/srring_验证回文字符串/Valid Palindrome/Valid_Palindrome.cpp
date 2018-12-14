#include<stdio.h>
#include <string>
using std::string;

// ��һ�ַ���
// https://www.cnblogs.com/17bdw/p/10117910.html#_label1_0
// �ڶ��ַ���
// https ://leetcode.com/problems/valid-palindrome/discuss/119173/C++-Easy-to-Understand-Solution


class Solution {
public:
	bool isPalindrome(string s) {

		string re_val = "";
        // ��ȥ������ţ���ȡ���ַ�����Сд��ĸ
		for (char str_val : s)
		{
			// ȷ����ĸ����
			if (isalnum(str_val) != false)
			{
				if (str_val >= 'A'&& str_val <= 'Z')
				{
					// ȡСд���д֮��Ĳ�ֵ���õ��ַ���Ӧ��СдASCII���Ӧ��ʲô����ַ�����
					re_val += (str_val + ('a' - 'A'));
				}
				else
				{
					// �����Сд�Ͳ�����
					re_val += str_val;
				}
			}
		}
		for (int i=0,j=re_val.size()-1; i<j;i++,j--) 
		{
			//һ��ָ������ָ���ұߣ�һ��ָ����ұ�ָ����ߡ�����в�ͬ��ֵ�����жϲ��ǻ����ַ���
			if (re_val[i] != re_val[j])
				return false;
		}
    	return true;
	}
};


int main()
{

	Solution solu;
	bool ret;
	ret = solu.isPalindrome("A man, a plan, a canal: Panama");
	printf("%d \n", ret);
	ret = solu.isPalindrome("race a car");
	printf("%d \n", ret);
	return 0;
}