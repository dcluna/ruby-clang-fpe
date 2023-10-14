#include "ruby_clang_fpe.h"
#include "fpe.h"
#include "fpe_locl.h"

VALUE rb_mRubyClangFpe;

size_t
fpe_get_size (const void *dsize){ return sizeof(dsize); };

static const rb_data_type_t fpe_type = {
  "fpe",
  { 0, RUBY_DEFAULT_FREE, fpe_get_size, },
  0, 0,
  RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE ffpe_alloc(VALUE);

static VALUE rb_cFpe; // RubyClangFpe::FpeKey class
static VALUE rb_cFpe3; // RubyClangFpe::Fpe3Key class
static VALUE rb_cFpe3_1; // RubyClangFpe::Fpe31Key class
static VALUE rb_cFpe1; // RubyClangFpe::Fpe1Key class

static VALUE t_gen_ff3_key(VALUE self, VALUE key, VALUE tweak, VALUE radix)
{
  FPE_KEY *fpe_key;
  fpe_key = FPE_ff3_create_key(StringValuePtr(key), StringValuePtr(tweak), NUM2UINT(radix));
  if (fpe_key != NULL) {
    return TypedData_Wrap_Struct(rb_cFpe3, &fpe_type, fpe_key);
  } else {
    return Qnil;
  }
};

static VALUE t_gen_ff3_1_key(VALUE self, VALUE key, VALUE tweak, VALUE radix)
{
  FPE_KEY *fpe_key;
  fpe_key = FPE_ff3_1_create_key(StringValuePtr(key), StringValuePtr(tweak), NUM2UINT(radix));
  if (fpe_key != NULL) {
    return TypedData_Wrap_Struct(rb_cFpe3_1, &fpe_type, fpe_key);
  } else {
    return Qnil;
  }
};

static VALUE t_gen_ff1_key(VALUE self, VALUE key, VALUE tweak, VALUE radix)
{
  FPE_KEY *fpe_key;
  fpe_key = FPE_ff1_create_key(StringValuePtr(key), StringValuePtr(tweak), NUM2UINT(radix));
  if (fpe_key != NULL) {
    return TypedData_Wrap_Struct(rb_cFpe1, &fpe_type, fpe_key);
  } else {
    return Qnil;
  }
};

static VALUE t_ff3_encrypt(VALUE self, VALUE plaintext)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  char *plaintext_str = StringValueCStr(plaintext);
  char ciphertext[strlen(plaintext_str)];
  FPE_ff3_encrypt(plaintext_str, ciphertext, fpe_key_ptr);
  return rb_str_new_cstr(ciphertext);
};

static VALUE t_ff3_decrypt(VALUE self, VALUE ciphertext)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  char plaintext[strlen(StringValueCStr(ciphertext))];
  FPE_ff3_decrypt(StringValuePtr(ciphertext), plaintext, fpe_key_ptr);
  return rb_str_new_cstr(plaintext);
};

static VALUE t_ff1_encrypt(VALUE self, VALUE plaintext)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  char ciphertext[strlen(StringValueCStr(plaintext))];
  FPE_ff1_encrypt(StringValuePtr(plaintext), ciphertext, fpe_key_ptr);
  return rb_str_new_cstr(ciphertext);
};

static VALUE t_ff1_decrypt(VALUE self, VALUE ciphertext)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  char plaintext[strlen(StringValueCStr(ciphertext))];
  FPE_ff1_decrypt(StringValueCStr(ciphertext), plaintext, fpe_key_ptr);
  return rb_str_new_cstr(plaintext);
};

/*
 * call-seq:
 *  FpeKey.radix -> Integer
 *
 * Returns the integer value of the radix used to generate the key.
 *
 */
static VALUE t_radix(VALUE self)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  return UINT2NUM(fpe_key_ptr->radix);
};

static VALUE t_tweak(VALUE self)
{
  FPE_KEY *fpe_key_ptr;
  TypedData_Get_Struct(self, FPE_KEY, &fpe_type, fpe_key_ptr);
  return rb_str_new_cstr(fpe_key_ptr->tweak);
};

void
Init_ruby_clang_fpe(void)
{
  rb_mRubyClangFpe = rb_define_module("RubyClangFpe");
  rb_cFpe = rb_define_class_under(rb_mRubyClangFpe, "FpeKey", rb_cObject);
  rb_cFpe3 = rb_define_class_under(rb_mRubyClangFpe, "Fpe3Key", rb_cFpe);
  rb_cFpe3_1 = rb_define_class_under(rb_mRubyClangFpe, "Fpe31Key", rb_cFpe);
  rb_cFpe1 = rb_define_class_under(rb_mRubyClangFpe, "Fpe1Key", rb_cFpe);
  rb_define_singleton_method(rb_cFpe, "generate_ff3_key", t_gen_ff3_key, 3);
  rb_define_singleton_method(rb_cFpe, "generate_ff3_1_key", t_gen_ff3_1_key, 3);
  rb_define_singleton_method(rb_cFpe, "generate_ff1_key", t_gen_ff1_key, 3);
  rb_define_method(rb_cFpe, "radix", t_radix, 0);
  rb_define_method(rb_cFpe, "tweak", t_tweak, 0);
  rb_define_method(rb_cFpe3, "encrypt", t_ff3_encrypt, 1);
  rb_define_method(rb_cFpe3_1, "encrypt", t_ff3_encrypt, 1);
  rb_define_method(rb_cFpe1, "encrypt", t_ff1_encrypt, 1);
  rb_define_method(rb_cFpe3, "decrypt", t_ff3_decrypt, 1);
  rb_define_method(rb_cFpe3_1, "decrypt", t_ff3_decrypt, 1);
  rb_define_method(rb_cFpe1, "decrypt", t_ff1_decrypt, 1);
}
