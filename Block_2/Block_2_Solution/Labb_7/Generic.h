// 2016-03-20 Daniel Stenekap och Göran Forström

#ifndef GENERIC_H
#define GENERIC_H

#ifndef TRUE
#define TRUE -1
#define FALSE 0
#endif // !TRUE

// Defines för flushRestOfLine
#define C_RADSLUT 10

// Defines for readLine
#define C_BUFFER_SIZE 80

void systemAbort(char* ir_message);
static void flushRestOfLine(void);
int yesNoRepeater(char ir_prompt[]);
int readLine(char* ior_chArr, int i_sizeChArr);
int inputIntGreaterThanLimit(char * ir_PromptChArr, int i_limit);
void inputStrWithDefault(char * ir_promptStr, char * ior_Str, int i_maxLen, int i_editFlag);
void inputFloatWithDefault(char * ir_promptStr, float * ior_Float, int i_editFlag);

#endif // GENERIC_H
