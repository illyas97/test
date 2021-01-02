#include "httpd.h"
#include <stdlib.h>

int main(int c, char **v) {
  serve_forever("8000");
  return 0;
}

void route() {
  ROUTE_START()

  ROUTE_GET("/") {
	FILE *fp;
	char *buff;
	int html_size = 65535;
	buff = malloc(html_size);
	fp = fopen("index.html", "r");
	printf("HTTP/1.1 200 OK\r\n\r\n");
	while((fgets(buff, 65535, (FILE*)fp)) != NULL)
	{
		printf("%s\n", buff );
	}
		free(buff);
		fclose(fp);
 }

  ROUTE_GET("/test") {
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("List of request headers:\r\n\r\n");

    header_t *h = request_headers();

    while (h->name) {
      printf("%s: %s\n", h->name, h->value);
      h++;
    }
  }

  ROUTE_POST("/") {
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("Wow, seems that you POSTed %d bytes. \r\n", payload_size);
    printf("Fetch the data using `payload` variable.");
  }

  ROUTE_END()
}
