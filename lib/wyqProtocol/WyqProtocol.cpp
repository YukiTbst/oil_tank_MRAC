#include "WyqProtocol.h"
bool command_check(String cmd_rec)
{
    int chars=0;
    int ints=0;
    int syms=0;
    int checker=100;
    int idx=cmd_rec.indexOf('~');
    if(idx<0)
    {
        return false;
    }
    if(cmd_rec.substring(0,3)!=String("wyq"))
    {
        return false;
    }
    for(int i=0;i<idx;i++)
    {
        if(isAlpha(cmd_rec[i]))
        {
            chars++;
            continue;
        }
        if(isAlphaNumeric(cmd_rec[i]))
        {
            ints++;
            continue;
        }
        syms++;
    }
    checker=cmd_rec.substring(idx+1).toInt();
    if(checker==chars-ints+syms*2)
    {
        return true;
    }
    return false;
}
String check_bytes_cal(String cmd_str)
{
    int chars=0;
    int ints=0;
    int syms=0;
    for(int i=0;i<cmd_str.length();i++)
    {
        if(isAlpha(cmd_str[i]))
        {
            chars++;
            continue;
        }
        if(isAlphaNumeric(cmd_str[i]))
        {
            ints++;
            continue;
        }
        syms++;
    }
    return String("~")+String(chars-ints+syms*2)+String("\n");
}
void check_bytes_append(String &cmd_str)
{
    cmd_str+=check_bytes_cal(cmd_str)+"\n";
    return;
}