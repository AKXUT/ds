/*************************************************
 * Created by David on Wed Oct 10 08:48:48 2018  *
 *************************************************/

// 代码超链接地址：https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
// 这是一份Next表的0号下标从0开始的KMP实现算法（区别于课本上和wiki上Next表的0号下标从-1开始）
// 两种Next表的构造过程是一样的，只是具体到程序实现有点区别，geeksforgeeks上的版本更好理解。
// wiki上的版本原始版和优化版，gfg上的是原始版。


#include <stdio.h> 
#include <string.h>
void computeLPSArray(char* pat, int M, int* lps); 

// Prints occurrences of txt[] in pat[] 
void KMPSearch(char* pat, char* txt) {
  int M = strlen(pat);
  int N = strlen(txt);
  // create lps[] that will hold the longest prefix suffix
  // values for pattern
  int lps[M];

  // Preprocess the pattern (calculate lps[] array) 
  computeLPSArray(pat, M, lps);
  int i = 0; // index for txt[]
  int j = 0; // index for pat[]
  while (i < N) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }
    if (j == M) {
      printf("Found pattern at index %d \n", i - j);
      j = lps[j - 1];
    }
    // mismatch after j matches 
    else if (i < N && pat[j] != txt[i]) { 
      // Do not match lps[0..lps[j-1]] characters, 
      // they will match anyway 
      if (j != 0) 
	j = lps[j - 1]; 
      else
	i = i + 1; 
    } 
  } 
} 

// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps) 
{ 
  // length of the previous longest prefix suffix 
  int len = 0; 
  lps[0] = 0; // lps[0] is always 0 

  // the loop calculates lps[i] for i = 1 to M-1 
  int i = 1; 
  while (i < M) { 
    if (pat[i] == pat[len]) { 
      len++; 
      lps[i] = len; 
      i++; 
    } 
    else { // (pat[i] != pat[len])  
	// This is tricky. Consider the example. 
	// AAACAAAA and i = 7. The idea is similar 
	// to search step. 
	if (len != 0) { 
	  len = lps[len - 1]; 
	  // Also, note that we do not increment 
	  // i here 
	} 
	else { // if (len == 0)
	  lps[i] = 0;
	  i++;
	}
    } 
  } 
} 

// Driver program to test above function 
int main() 
{ 
  //char txt[] = "ABABDABACDABABCABAB"; 
  //char pat[] = "ABAB";
  char txt[] = "ABC ABCDAB ABCDABCDABDE"; 
  char pat[] = "ABCDABD";
  KMPSearch(pat, txt); 
  return 0; 
} 
