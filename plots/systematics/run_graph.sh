\rm jet_ph_assoc.exe
#g++ `root-config --cflags --libs` -L/opt/products/dcache/1.2.42/lib -ldcap  jet_ph_assoc_13_Peter.cxx -o jet_ph_assoc.exe
g++ `root-config --cflags --libs` -L/opt/products/dcache/1.2.42/lib -ldcap  systematic_draw_graph_2_5.cxx -o jet_ph_assoc.exe
#g++ `root-config --cflags --libs` -L/opt/products/dcache/1.2.42/lib -ldcap  show_jets_promtph_2.cxx -o jet_ph_assoc.exe
./jet_ph_assoc.exe
#root -l
