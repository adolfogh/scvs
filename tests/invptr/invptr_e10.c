/*	Rule: invptr	Test File: invptr_e10.c
 *
 * Copyright (c) 2012 Carnegie Mellon University.
 * All Rights Reserved.
 *  
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions
 * are met:
 *  
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following acknowledgments 
 *    and disclaimers.
 *  
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the 
 *    distribution.
 *  
 * 3. The names “Carnegie Mellon University,” "CERT” and/or “Software
 *    Engineering Institute" shall not be used to endorse or promote 
 *    products derived from this software without prior written 
 *    permission. For written permission, please contact 
 *    permission@sei.cmu.edu.
 *  
 * 4. Products derived from this software may not be called "CERT" 
 *    nor may "CERT" appear in their names without prior written 
 *    permission of permission@sei.cmu.edu.
 *  
 * 5. Redistributions of any form whatsoever must retain the following 
 *    acknowledgment:
 *  
 * "This product includes software developed by CERT with funding and 
 *  support from the Department of Defense under Contract No. FA 
 *  8721-05-C-0003.  The U.S. Government's rights to use, modify,
 *  reproduce, release, perform, display, or disclose this material are
 *  restricted by the Rights in Technical Data-Noncommercial Items
 *  clauses (DFAR 252-227.7013 and DFAR 252-227.7013 Alternate I contained
 *  in the foregoing identified contract.
 *  
 *  THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY “AS IS” AND
 *  CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AS TO ANY MATTER, AND ALL SUCH WARRANTIES,
 *  INCLUDING WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE, ARE EXPRESSLY DISCLAIMED.  WITHOUT LIMITING THE GENERALITY OF
 *  THE FOREGOING, CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY
 *  OF ANY KIND RELATING TO EXCLUSIVITY, INFORMATIONAL CONTENT, ERROR-FREE
 *  OPERATION, RESULTS TO BE OBTAINED FROM USE, FREEDOM FROM PATENT,
 *  TRADEMARK AND COPYRIGHT INFRINGEMENT AND/OR FREEDOM FROM THEFT OF TRADE
 *  SECRETS.”
 * 
 *
 * Rule: [invptr]
 * Description: diagnostic is required because the expression first++ 
 *              results in a pointer beyond the end of the array buf 
 *              when buf contains no elements.
 * Diagnostic: required on line 84
 * Additional Test Files: None
 * Command-line Options: None
 */

#include <stdlib.h>
#include <string.h>

struct S {
  size_t len;
  char buf[];
};

char *find(struct S *, int);
char *find_period(const char *);

int main(void) {
  const char *lcc = "/home/user/.profile";

  char *first_period = find_period(lcc);

  return EXIT_SUCCESS;
}

char *find(struct S *s, int c) {
  char *first = s->buf;
  char *last = s->buf + s->len;

  while (first++ != last) {  // diagnostic required
    if (*first == (unsigned char)c) {
      return first;
    }
  }

  return NULL;
}
 
char *find_period(const char *cc) {
  int period = '.';
  struct S *s = (struct S *)malloc(sizeof(struct S));
  if(s) {
    s->len = 0;
    return find(s, period);
  } else {
    return NULL;
  }
}

