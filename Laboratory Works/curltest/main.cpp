#define CURL_STATICLIB
#include <iostream>
#include <curl/curl.h> 


int main()
{
	CURL* curl = curl_easy_init();

	return 0;
}