#ifndef YASL_YASL_OBJECT_H_
#define YASL_YASL_OBJECT_H_

#include "data-structures/YASL_String.h"
#include "yasl_conf.h"
#include "yasl_types.h"
// #include "interpreter/closure.h"

#define UNDEF_C ((struct YASL_Object){ .type = Y_UNDEF, .value = { .ival = 0 }  })
#define FALSE_C ((struct YASL_Object){ .type = Y_BOOL, .value = {.ival = 0 }})
#define TRUE_C ((struct YASL_Object){ .type = Y_BOOL, .value = {.ival = 1 }})

#define YASL_END() ((struct YASL_Object){ .type = Y_END, .value = {.ival = 0}})
#define YASL_UNDEF() ((struct YASL_Object){ .type = Y_UNDEF, .value = {.ival = 0 }})
#define YASL_FLOAT(d) ((struct YASL_Object){ .type = Y_FLOAT, .value = {.dval = d }})
#define YASL_INT(i) ((struct YASL_Object){ .type = Y_INT, .value = {.ival = i }})
#define YASL_BOOL(b) ((struct YASL_Object){ .type = Y_BOOL, .value = {.ival = b }})
#define YASL_STR(s) ((struct YASL_Object){ .type = Y_STR, .value = {.sval = s }})
#define YASL_LIST(l) ((struct YASL_Object){ .type = Y_LIST, .value = {.uval = l }})
#define YASL_TABLE(t) ((struct YASL_Object){ .type = Y_TABLE, .value = {.uval = t }})
#define YASL_USERDATA(p) ((struct YASL_Object){ .type = Y_USERDATA, .value = {.uval = p }})
#define YASL_USERPTR(p) ((struct YASL_Object){ .type = Y_USERPTR, .value = {.pval = p }})
#define YASL_FN(f) ((struct YASL_Object){ .type = Y_FN, .value = {.fval = f }})
#define YASL_CFN(f, n) ((struct YASL_Object){ .type = Y_CFN, .value = {.cval = new_cfn(f, n) }})

#define YASL_ISFLOAT(v) ((v).type == Y_FLOAT)

#define YASL_GETFLOAT(v) ((v).value.dval)
#define YASL_GETINT(v) ((v).value.ival)
#define YASL_GETNUM(v) (YASL_ISFLOAT(v) ? YASL_GETFLOAT(v) : YASL_GETINT(v))
#define YASL_GETBOOL(v) ((v).value.ival)
#define YASL_GETSTR(v) ((v).value.sval)
#define YASL_GETLIST(v) ((struct YASL_List *)((v).value.uval->data))
#define YASL_GETTABLE(v) ((struct YASL_Table *)((v).value.uval->data))
#define YASL_GETUSERDATA(v) ((v).value.uval)
#define YASL_GETUSERPTR(v) ((v).value.pval)
#define YASL_GETFN(v) ((v).value.fval)
#define YASL_GETCFN(v) ((v).value.cval)

struct YASL_State;
struct RC_UserData;
struct Closure;

struct YASL_Object {
	enum YASL_Types type;
	union {
		yasl_int ival;
		yasl_float dval;
		struct YASL_String *sval;
		struct RC_UserData *uval;
		struct CFunction *cval;
		struct Closure *lval;
		unsigned char *fval;
		void *pval;
	} value;
};

struct CFunction {
	struct RC *rc;
	int num_args;
	int (*value)(struct YASL_State *);
};

struct CFunction *new_cfn(int (*value)(struct YASL_State *), int num_args);
void cfn_del_rc(struct CFunction *cfn);
void cfn_del_data(struct CFunction *cfn);

struct YASL_Object *YASL_String(struct YASL_String *str);
struct YASL_Object *YASL_Table(void);

/*
 * Either both types are strings or both types are numerical. Otherwise error
 */
int yasl_object_cmp(struct YASL_Object a, struct YASL_Object b);

bool ishashable(const struct YASL_Object *const v);
bool isfalsey(struct YASL_Object v);
struct YASL_Object isequal(const struct YASL_Object *const a, const struct YASL_Object *const b);
int print(struct YASL_Object a);

inline bool obj_isundef(const struct YASL_Object *const v) {
	return v->type == Y_UNDEF;
}

inline bool obj_isfloat(const struct YASL_Object *const v) {
	return v->type == Y_FLOAT;
}

inline bool obj_isint(const struct YASL_Object *const v) {
	return v->type == Y_INT;
}

inline bool obj_isnum(const struct YASL_Object *const v) {
	return obj_isint(v) || obj_isfloat(v);
}


inline bool obj_isbool(const struct YASL_Object *const v) {
	return v->type == Y_BOOL;
}

inline bool obj_isstr(const struct YASL_Object *const v) {
	return v->type == Y_STR;
}

inline bool obj_islist(const struct YASL_Object *const v) {
	return v->type == Y_LIST;
}

inline bool obj_istable(const struct YASL_Object *const v) {
	return v->type == Y_TABLE;
}

inline bool obj_isuserdata(const struct YASL_Object *const v) {
	return v->type == Y_USERDATA;
}

inline bool obj_isuserptr(const struct YASL_Object *const v) {
	return v->type == Y_USERPTR;
}

inline bool obj_isfn(const struct YASL_Object *const v) {
	return v->type == Y_FN;
}

inline bool obj_isclosure(const struct YASL_Object *const v) {
	return v->type == Y_CLOSURE;
}

inline bool obj_iscfn(const struct YASL_Object *const v) {
	return v->type == Y_CFN;
}

void inc_ref(struct YASL_Object *v);
void dec_ref(struct YASL_Object *v);

#endif
