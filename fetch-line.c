#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fetch-line.h"

// Trims the line if it is too long.
static char *trim_line(char *s)
{
	char *end;

	while(isspace((unsigned char)*s)) s++;

	if(*s == 0)
		return s;

	end = s + strlen(s) - 1;
	while(end > s && (isspace((unsigned char)*end) || *end == '#')) end--;

	*(end + 1) = 0;

	return s;	
}

// Fetches a line of text from the stream.
char *fetch_line(char *buf, int buflen, FILE *stream, int *lineno)
{
	char *s;
	if (fgets(buf, buflen, stream) == NULL)
		return NULL;
	++*lineno;
	if (buf[strlen(buf) - 1] != '\n') {
		fprintf(stderr, "*** reading error: input line %d too long for %s's buf[%d]\n", *lineno, __func__, buflen);
		exit(EXIT_FAILURE);
	}
	s = trim_line(buf);
	if (*s != '\0')
		return s;
	else
		return fetch_line(buf, buflen, stream, lineno);
}