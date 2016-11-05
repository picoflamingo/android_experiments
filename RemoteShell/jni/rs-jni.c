//#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

#include <jni.h>
#include <android/log.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/prctl.h>
#include <errno.h> 

#define logv(...) __android_log_print (ANDROID_LOG_VERBOSE, "RShell", __VA_ARGS__)

void
Java_com_papermintdesigns_remoteshell_RemoteShell_runDaemon (JNIEnv *env, jobject thiz)
{
  struct sockaddr_in   server, client;
  socklen_t            len = sizeof (struct sockaddr_in);
  int                  s,s1, sid;
  pid_t                pid;

  logv ("Remote Shell Seasonal Greetings!\n");  
  /* try to become a daemon */
  pid = fork ();
  if (pid < 0) exit (1);
  if (pid != 0) return;

#if 0
  // Do the double fork
  pid = fork ();
  if (pid < 0) exit (1);
  if (pid != 0) return;
#endif

  if ((sid = setsid()) < 0)
    logv ("Setsid error (%s)\n", strerror (errno));
  
  logv ("Starting server with sid:%d \n", sid);
  
  while (1)
    {
      logv ("Starting Server...\n");
      
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_family = AF_INET;
      server.sin_port = htons(8080);
      
      s = socket (PF_INET, SOCK_STREAM, 0);
      if (s < 0)
	logv ("Cannot create socket (%s)\n", strerror (errno));
      
      if ((bind (s, (struct sockaddr *) &server, sizeof (server)))< 0)
	logv ("Cannot Bind (%s)\n", strerror (errno));
      
      listen (s, 10);
      
      while (1)
	{
	  //char buffer[2048];
	  
	  s1 = accept (s, (struct sockaddr *)&client, &len);
	  if (s1 < 0)
	    {
	      logv("Cannot accept connection (%s)\n", strerror (errno));
	    }
	  
	  pid_t pid ;
	  char *name[3] ;
	  
	  // Create a process to serve this shell session
	  if ((pid = fork ()) < 0)
	    write (2, "Cannot create process\n", 22);
	  else
	    {
	      if (pid) close (s1);
	      else
		{
		  // Dup fds
		  dup2 (s1, 0);
		  dup2 (s1, 1);
		  dup2 (s1, 2);
		  name[0] = "/system/bin/sh";
		  name[1] = "-i";
		  name[2] = NULL;
		  execv (name[0], name );
		  exit (1);
		}
	    }
	    
	}
    }
  logv ("DONE!\n");
  
}
