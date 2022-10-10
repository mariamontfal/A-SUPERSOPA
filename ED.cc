#ifndef ED_FILE
#define ED_FILE

enum SearchResult {
    WORD_FOUND,
    WORD_NOT_FOUND,
    SUBWORD_NOT_FOUND
};

enum BacktrackingAction {
    ADD_WORD_AND_SEARCH,
    CONTINUE_SEARCHING,
    END_SEARCH
};

class EstructuraDades {

private:

    // Variables que permitan el calculo de experimentos
    // o no, quizas no hacen falta, por ejemplo:
    // double tiempoMedioEjecucion;

public:

    EstructuraDades() {}

    static BacktrackingAction evalSearchResult(SearchResult sr) {
        switch(sr) {
            case SearchResult::WORD_FOUND:
                return BacktrackingAction::ADD_WORD_AND_SEARCH;
            case SearchResult::WORD_NOT_FOUND:
                return BacktrackingAction::CONTINUE_SEARCHING;
            case SearchResult::SUBWORD_NOT_FOUND:
                return BacktrackingAction::END_SEARCH;
            default:
                throw std::invalid_argument("Search result not valid...");
                return BacktrackingAction::END_SEARCH;
        }
    }

};

#endif