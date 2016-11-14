struct File {
  static File *Create(const char *);
  void Close();
};

extern bool need_to_restart();

void work(const char *fn) {
  File *f = File::Create(fn);
  if(f) {
    // work...
    if(need_to_restart()) {
      f->Close();
      f = File::Create(fn);
      if(f) {
        // more work...
      }
    }
    f->Close();
  }
}
