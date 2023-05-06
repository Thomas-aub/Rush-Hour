CXX      = g++

.DEFAULT_GOAL := rush_hour

SOURCES =
# SOURCES += rush_hour.cpp
SOURCES += case.cpp
SOURCES += vehicule.cpp
SOURCES += plateau.cpp

OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS  += -g -Wall -std=c++11 -pedantic
LDFLAGS +=

$(OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 

########## RUSH HOUR ##########

# LISTE_SOURCES = test_liste.cpp
LISTE_SOURCES = rush_hour.cpp
LISTE_OBJECTS = $(LISTE_SOURCES:.cpp=.o)

rush_hour : $(LISTE_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(LISTE_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)

$(LISTE_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : rush_hour
TARGETS += rush_hour
CLEAN_OBJECTS += $(LISTE_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
