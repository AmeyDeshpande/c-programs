#ifndef NAUSEA_H
#define NAUSEA_H
class Nausea {
  public:
    Nausea& operator=(const Nausea&);
    Nausea(const Nausea&);
    Nausea();
    enum throw_where {copy_ctor, default_ctor, assignment_op, nowhere };
    static throw_where type;
    static unsigned int trigger;
};
#endif
