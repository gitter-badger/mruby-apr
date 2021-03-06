/*
 * apr_skiplist
 * Defined in file apr_skiplist.h @ line 54
 */

/*
 * TODO: INCLUDES
 */

#include "mruby_APR.h"

#if BIND_AprSkiplist_TYPE

/*
 * Class Methods
 */

#if BIND_AprSkiplist_INITIALIZE
mrb_value
mrb_APR_AprSkiplist_initialize(mrb_state* mrb, mrb_value self) {
  apr_skiplist* native_object = (apr_skiplist*)malloc(sizeof(apr_skiplist));
  mruby_gift_apr_skiplist_data_ptr(self, native_object);
  return self;
}
#endif

mrb_value
mrb_APR_AprSkiplist_disown(mrb_state* mrb, mrb_value self) {
  mrb_value ruby_object;
  mrb_get_args(mrb, "o", &ruby_object);

  if (!mrb_obj_is_kind_of(mrb, ruby_object, mrb_class_ptr(self))) {
    mrb_raise(mrb, E_TYPE_ERROR, "APR::AprSkiplist.disown only accepts objects of type APR::AprSkiplist");
    return mrb_nil_value();
  }

  ((mruby_to_native_ref*)(DATA_PTR(ruby_object)))->belongs_to_ruby = FALSE;

  return mrb_nil_value();
}

mrb_value
mrb_APR_AprSkiplist_belongs_to_ruby(mrb_state* mrb, mrb_value self) {
  mrb_value ruby_object;
  mrb_get_args(mrb, "o", &ruby_object);

  if (!mrb_obj_is_kind_of(mrb, ruby_object, mrb_class_ptr(self))) {
    mrb_raise(mrb, E_TYPE_ERROR, "APR::AprSkiplist.disown only accepts objects of type APR::AprSkiplist");
    return mrb_nil_value();
  }

  if ( ((mruby_to_native_ref*)(DATA_PTR(ruby_object)))->belongs_to_ruby ) {
    return mrb_true_value();
  } else {
    return mrb_false_value();
  }
}


void mrb_APR_AprSkiplist_init(mrb_state* mrb) {
  struct RClass* AprSkiplist_class = mrb_define_class_under(mrb, APR_module(mrb), "AprSkiplist", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprSkiplist_class, MRB_TT_DATA);

#if BIND_AprSkiplist_INITIALIZE
  mrb_define_method(mrb, AprSkiplist_class, "initialize", mrb_APR_AprSkiplist_initialize, MRB_ARGS_NONE());
#endif
  mrb_define_class_method(mrb, AprSkiplist_class, "disown", mrb_APR_AprSkiplist_disown, MRB_ARGS_ARG(1, 0));
  mrb_define_class_method(mrb, AprSkiplist_class, "belongs_to_ruby?", mrb_APR_AprSkiplist_belongs_to_ruby, MRB_ARGS_ARG(1, 0));


}

#endif
