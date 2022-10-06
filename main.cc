#include "diccBloomFilter.h"

int main(){
vector<string> entrada = { "abound",   "abounds",       "abundance",
    "abundant", "accessible",    "bloom",
    "blossom",  "bolster",       "bonny",
    "bonus",    "bonuses",       "coherent",
    "cohesive", "colorful",      "comely",
    "comfort",  "gems",          "generosity",
    "generous", "generously",    "genial",
    "bluff",    "cheater",       "hate",
    "war",      "humanity",      "racism",
    "hurt",     "nuke",          "gloomy",
    "facebook", "geeksforgeeks", "twitter" };

BloomFilter bm = BloomFilter(entrada);
cout<<bm.findWord("facebook")<<endl;
cout<<bm.findWord("face")<<endl;
cout<<bm.findWord("generous")<<endl;
cout<<bm.findWord("hola")<<endl;

cout<<bm.getN()<<endl;
bm.addWord("hola");
/*bm.addWord("holap");
bm.addWord("holat");
bm.addWord("holaf");
bm.addWord("holag");
bm.addWord("holad");
bm.addWord("holas");
bm.addWord("holaa");
bm.addWord("holaaaa");
bm.addWord("holaaaaaa");
bm.addWord("holqqqqa");
bm.addWord("howla");
bm.addWord("hoela");
bm.addWord("hotttla");
bm.addWord("holttttta");
bm.addWord("holtttttttta");
cout<<bm.getProbability()<<endl;
cout<<bm.getM()<<endl;
cout<<bm.getK()<<endl;
cout<<bm.getN()<<endl;

bm.addWord("holplfa");
cout<<bm.getProbability()<<endl;
cout<<bm.getM()<<endl;
cout<<bm.getK()<<endl;
cout<<bm.getN()<<endl;
bm.addWord("holllla");
bm.addWord("holaaaaaa");
bm.addWord("holxxxa");
bm.addWord("holcccca");
bm.addWord("holvvvva");
bm.addWord("holaqqqq");
bm.addWord("houiola");
bm.addWord("holsjdla");
bm.addWord("holqlwjea");

cout<<bm.getN()<<endl;
cout<<bm.getProbability()<<endl;
cout<<bm.findWord("hola")<<endl;*/
}
