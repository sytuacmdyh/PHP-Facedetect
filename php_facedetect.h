/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | This source file is subject to BSD 3-Clause license,                 |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://opensource.org/licenses/BSD-3-Clause.                         |
  | If you did not receive a copy of the BSD license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | robert@xarg.org so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Robert Eisele <robert@xarg.org>                              |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_FACEDETECT_H
#define PHP_FACEDETECT_H

#define PHP_FACEDETECT_VERSION "1.1.0"
#define PHP_FACEDETECT_EXTNAME "facedetect"

#ifdef ZTS
# include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(facedetect);

PHP_FUNCTION(object_detect);
PHP_FUNCTION(object_count);

extern zend_module_entry facedetect_module_entry;
#define phpext_facedetect_ptr &facedetect_module_entry

#endif

