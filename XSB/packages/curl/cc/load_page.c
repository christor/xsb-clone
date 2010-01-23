/*
** File: packages/curl/cc/load_page.c
** Author: Aneesh Ali
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 2010
** 
** XSB is free software; you can redistribute it and/or modify it under the
** terms of the GNU Library General Public License as published by the Free
** Software Foundation; either version 2 of the License, or (at your option)
** any later version.
** 
** XSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
** more details.
** 
** You should have received a copy of the GNU Library General Public License
** along with XSB; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
*/

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "common.h"

struct result_t
{
  size_t size;
  size_t len;
  char *data;
};

/*
 * Write data callback function (called within the context of 
 * curl_easy_perform.
 */
static size_t
write_data (void *buffer, size_t size, size_t nmemb, void *userp)
{
  struct result_t *result = userp;

  while (result->len + (size * nmemb) >= result->size)
    {

      result->data = realloc (result->data, result->size * 2);
      result->size *= 2;
    }

  memcpy (result->data + result->len, buffer, size * nmemb);
  result->len += size * nmemb;

  result->data[result->len] = 0;

  return size * nmemb;
}

char *
load_page (char *source, curl_opt options, char ** source_final)
{
  CURL *curl;
  CURLcode ret;
  char * EMPTY_STRING = "";
  char * source_enc;
  char * url = NULL;
  struct result_t result;

  /* First step, init curl */
  curl = curl_easy_init ();
  if (!curl)
    {
      printf ("couldn't init curl\n");
      return 0;
    }

  memset (&result, 0, sizeof (result));
  result.size = 1024;
  result.data = (char *) calloc (result.size, sizeof (char));

  source_enc = curl_easy_unescape(curl , source , 0, 0);
  strcpy(source, source_enc);
  curl_free(source_enc);

  /* Tell curl the URL of the file we're going to retrieve */
  curl_easy_setopt (curl, CURLOPT_URL, source);

  /* Tell curl that we'll receive data to the function write_data, and
   * also provide it with a context pointer for our error return.
   */
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, &result);

  /* Redirect */
  curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, options.redir_flag);

  /* Verify the certificate */
  curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, options.secure.flag);
  curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, options.secure.flag * 2);
  curl_easy_setopt (curl, CURLOPT_CAINFO, options.secure.crt_name);

  /* Allow curl to perform the action */
  ret = curl_easy_perform (curl);

  curl_easy_getinfo (curl, CURLINFO_EFFECTIVE_URL, &url);
  *source_final = malloc((strlen(url) + 1)*sizeof(char));
  strcpy(*source_final, url);

  curl_easy_cleanup (curl);

  if (result.len > 0)
    return result.data;

  free (result.data);
  return EMPTY_STRING;
}

void *
encode (char *url, char **dir, char **file)
{
  int dir_len = 0;
  char *dir_enc = NULL;

  *file = strrchr (url, '/');
  if (*file == NULL)
    *file = url;
  else 
  {
    (*file)++;
    dir_len = strlen(url) - strlen(*file) - 1;
  }

  *dir = (char *) malloc ((dir_len + 1) * sizeof (char));
  strncpy(*dir, url, dir_len);
  (*dir)[dir_len] = '\0';

  dir_enc = curl_easy_escape (NULL, *dir, 0);
  *dir = realloc (*dir, (strlen(dir_enc) + 1) * sizeof (char));
  strcpy (*dir, dir_enc);
  curl_free (dir_enc);

  return 0;
}