//
// Created by Administrator on 2024/6/7.
//
#include "Parent.h"
#include "stdio.h"

struct ParentPriv {
  // public field (just copy)
  int public_var;

  void (*public_func)(struct Parent *this);

  void (*private_var_setter)(struct Parent *this, int private_var);

  int (*private_var_getter)(struct Parent *this);

  void (*print)(struct Parent *this);

  // private field
  int private_var;

  void (*private_func)(struct Parent *this);
};

static void public_func(struct Parent *this) {
  struct ParentPriv *priv = (void *) this;
  printf("Parent.public_func, public_var: %d, private_var: %d\n", this->public_var, priv->private_var);
}

static void private_var_setter(struct Parent *this, int private_var) {
  struct ParentPriv *priv = (void *) this;
  priv->private_var = private_var;
}

static int private_var_getter(struct Parent *this) {
  struct ParentPriv *priv = (void *) this;
  return priv->private_var;
}

static void private_func(struct Parent *this) {
  struct ParentPriv *priv = (void *) this;
  printf("Parent.private_func, public_var: %d, private_var: %d\n", this->public_var, priv->private_var);
}

static void print(struct Parent *this) {
  struct ParentPriv *priv = (void *) this;
  printf("Parent.print, public_var: %d, private_var: %d\n", this->public_var, priv->private_var);
}

static struct Parent new(int public_var) {
  struct ParentPriv parent = {
      .public_var = public_var,
      .public_func = &public_func,
      .private_var_setter = &private_var_setter,
      .private_var_getter = &private_var_getter,
      .print = &print,
      .private_func = &private_func,
  };
  return *(struct Parent *) &parent;
}

const struct ParentClass Parent = {
    .new = &new,
};