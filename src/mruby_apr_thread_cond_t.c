/*
 * apr_thread_cond_t
 * Defined in file apr_thread_cond.h @ line 44
 */

/*
 * TODO: INCLUDES
 */

#include "mruby_APR.h"

#if BIND_AprThreadCondT_TYPE

/*
 * Class Methods
 */

#if BIND_AprThreadCondT_INITIALIZE
mrb_value
mrb_APR_AprThreadCondT_initialize(mrb_state* mrb, mrb_value self) {
  apr_thread_cond_t* native_object = (apr_thread_cond_t*)malloc(sizeof(apr_thread_cond_t));
  mruby_gift_apr_thread_cond_t_data_ptr(self, native_object);
  return self;
}
#endif

mrb_value
mrb_APR_AprThreadCondT_disown(mrb_state* mrb, mrb_value self) {
  mrb_value ruby_object;
  mrb_get_args(mrb, "o", &ruby_object);

  if (!mrb_obj_is_kind_of(mrb, ruby_object, mrb_class_ptr(self))) {
    mrb_raise(mrb, E_TYPE_ERROR, "APR::AprThreadCondT.disown only accepts objects of type APR::AprThreadCondT");
    return mrb_nil_value();
  }

  ((mruby_to_native_ref*)(DATA_PTR(ruby_object)))->belongs_to_ruby = FALSE;

  return mrb_nil_value();
}

mrb_value
mrb_APR_AprThreadCondT_belongs_to_ruby(mrb_state* mrb, mrb_value self) {
  mrb_value ruby_object;
  mrb_get_args(mrb, "o", &ruby_object);

  if (!mrb_obj_is_kind_of(mrb, ruby_object, mrb_class_ptr(self))) {
    mrb_raise(mrb, E_TYPE_ERROR, "APR::AprThreadCondT.disown only accepts objects of type APR::AprThreadCondT");
    return mrb_nil_value();
  }

  if ( ((mruby_to_native_ref*)(DATA_PTR(ruby_object)))->belongs_to_ruby ) {
    return mrb_true_value();
  } else {
    return mrb_false_value();
  }
}


void mrb_APR_AprThreadCondT_init(mrb_state* mrb) {
  struct RClass* AprThreadCondT_class = mrb_define_class_under(mrb, APR_module(mrb), "AprThreadCondT", mrb->object_class);
  MRB_SET_INSTANCE_TT(AprThreadCondT_class, MRB_TT_DATA);

#if BIND_AprThreadCondT_INITIALIZE
  mrb_define_method(mrb, AprThreadCondT_class, "initialize", mrb_APR_AprThreadCondT_initialize, MRB_ARGS_NONE());
#endif
  mrb_define_class_method(mrb, AprThreadCondT_class, "disown", mrb_APR_AprThreadCondT_disown, MRB_ARGS_ARG(1, 0));
  mrb_define_class_method(mrb, AprThreadCondT_class, "belongs_to_ruby?", mrb_APR_AprThreadCondT_belongs_to_ruby, MRB_ARGS_ARG(1, 0));


}

#endif
