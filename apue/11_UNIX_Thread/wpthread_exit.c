#include "apue.h"
#include <pthread.h>

struct foo {
    int                 f_count;
    pthread_mutex_t     f_lock;
    int                 f_id;
};

struct foo *
foo_alloc(int id) //allocate the object
{
    struct foo *fp;

    if((fp = malloc (sizeof(struct foo))) != NULL)
    {
    	fp->f_count = 1;
    	fp->f_id = id;
    	if(pthread_mutex_init(&fp->f_lock,NULL) != 0)
    	{
    		free(fp);
    		return (NULL);
    	}	

    	//countinue initialization
    }
    return (fp);
}

void foo_hold(struct foo *fp)   //add reference to the object
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}


void foo_rele(struct foo *fp) //release a reference to the object

{
	pthread_mutex_lock(&fp->f_lock);
	if( --fp->f_count == 0)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);

	}
	else 
		pthread_mutex_unlock(&fp->f_lock);

}