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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "ext/standard/info.h"
#include "php_facedetect.h"

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/photo/photo_c.h"
#include "opencv2/objdetect/objdetect_c.h"

#include <opencv2/opencv.hpp>
#include "opencv2/core/version.hpp"

#include "string"
using namespace std;
using namespace cv;

/* {{{ facedetect_functions[]
 *
 * Every user visible function must have an entry in facedetect_functions[].
 */
static zend_function_entry facedetect_functions[] = {
    PHP_FE(object_detect, NULL)
    PHP_FE(object_count, NULL)
    {NULL, NULL, NULL}
};
/* }}} */

/* {{{ facedetect_module_entry
 */
zend_module_entry facedetect_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_FACEDETECT_EXTNAME,
    facedetect_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(facedetect),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_FACEDETECT_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FACEDETECT
ZEND_GET_MODULE(facedetect)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINFO_FUNCTION(facedetect)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "facedetect support", "enabled");
	php_info_print_table_row(2, "facedetect version", PHP_FACEDETECT_VERSION);
	php_info_print_table_row(2, "OpenCV version", CV_VERSION);
	php_info_print_table_end();
}
/* }}} */


static void php_facedetect(INTERNAL_FUNCTION_PARAMETERS, int return_type)
{
	char *file, *casc;
	long flen, clen, myparam;

#ifdef ZEND_ENGINE_3
	zval array;
#else
	zval *array;
#endif
	zval *pArray;

	Mat srcImage, grayImage;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssl", &file, &flen, &casc, &clen, &myparam) == FAILURE) {
		RETURN_NULL();
	}

	CascadeClassifier cascade;
	if(!cascade.load( casc ) ) {
		RETURN_FALSE;
	}	

	Mat rawData  =  Mat( 1, flen, CV_8UC1, file );

	srcImage = imdecode(rawData, 0);
	if(!srcImage.data){
		RETURN_TRUE;
	}

	vector<Rect> rect;
	cascade.detectMultiScale(srcImage, rect, 1.1, myparam, 0);

	if(return_type) {

		array_init(return_value);

		if(rect.size() > 0) {
			int i;
			for(i = 0; i < rect.size(); i++) {
#ifdef ZEND_ENGINE_3
				ZVAL_NEW_ARR(&array);
				pArray = &array;
#else
				MAKE_STD_ZVAL(array);
				pArray = array;
#endif
				array_init(pArray);

				add_assoc_long(pArray, "x", rect[i].x);
				add_assoc_long(pArray, "y", rect[i].y);
				add_assoc_long(pArray, "w", rect[i].width);
				add_assoc_long(pArray, "h", rect[i].height);

				add_next_index_zval(return_value, pArray);
			}
		 }
	} else {
		RETVAL_LONG(rect.size());
	}

}

/* {{{ proto array object_detect(string picture_path, string cascade_file)
   Finds coordinates of faces (or in gernal "objects") on the given picture */
PHP_FUNCTION(object_detect)
{
	php_facedetect(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ proto int object_count(string picture_path, string cascade_file)
   Finds number of faces (or in gernal "objects") on the given picture*/
PHP_FUNCTION(object_count)
{
	php_facedetect(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

