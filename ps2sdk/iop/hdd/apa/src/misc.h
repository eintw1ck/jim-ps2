
#ifndef _MISC_H
#define _MISC_H

///////////////////////////////////////////////////////////////////////////////
//   Function declerations

int CdReadIlinkID(u8 *id, int *err);// not in ps2lib

void *allocMem(int size);
int getPs2Time(ps2time *tm);
void getPasswordHash(char *id, char *password1, char *password2);
int passcmp(char *password1, char *password2);
int getIlinkID(u8 *idbuf);

#endif /* _MISC_H */
