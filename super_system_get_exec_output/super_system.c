#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int super_system(const char * cmd, char *retmsg, int msg_len)
{
        FILE * fp;
        int res = -1;
        if (cmd == NULL || retmsg == NULL || msg_len < 0)
        {
                printf("Err: Fuc:%s nfs_system paramer invalid!\n", __func__);
                return 1;
        }
        if ((fp = popen(cmd, "r") ) == NULL)
        {
                perror("popen");
                printf("Err: Fuc:%s popen error: %s\n", __func__, strerror(errno));
                return 2;
        }
        else
        {
                memset(retmsg, 0, msg_len);
                while(fgets(retmsg, msg_len, fp));
                {
                        printf("Fuc: %s fgets buf is %s\n", __func__, retmsg);
                }
                if ( (res = pclose(fp)) == -1)
                {
                        printf("Fuc:%s close popen file pointer fp error!\n", __func__);
                        return 3;
                }
                //drop #012 from system result retmsg.
                retmsg[strlen(retmsg)-1] = '\0';
                return 0;
        }
}


int main()
{
	char *cmd = "whoami";
	char *cmd1 = "initctl list | grep process | wc -l";
	char retmsg[1024] = {0};
	int ret = 0;
	ret  = super_system(cmd, retmsg, sizeof(retmsg));
	printf("system nfs ret is %d retmsg is \n%s\n", ret, retmsg);
	return 0;
} 
