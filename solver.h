// Copyright 2019 SD_Homework_Team
#include "Hashtable.h"
#include "ListGraph.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <iomanip>
class sofer {
	public:
		bool online;
		float medie;
		int rating, distantaTotala, nrCurse, departareDeStart;
		std::string locatieActuala, nume;
		explicit sofer(std::string s, std::string name) {
			this->nume = name;
			this->locatieActuala = s;
			this->online = true;
			this->rating = 0;
			this->medie = 0.0f;
			this->distantaTotala = 0;
			this->nrCurse = 0;
			this->departareDeStart = 0;
		}
		~sofer() {}

};

int min(int a, int b) {
	if(a < b) {
		return a;
	}
	return b;
}

bool operator<(const sofer &a, const sofer &b) {
	if (a.departareDeStart == -1 && b.departareDeStart != -1) {
		return true;
	}
	if (a.departareDeStart != -1 && b.departareDeStart == -1) {
		return false;
	}
	if (a.departareDeStart > b.departareDeStart) {
		return true;
	}
	if (a.departareDeStart < b.departareDeStart) {
		return false;
	}
	if (a.medie < b.medie) {
		return true;
	}
	if (a.medie > b.medie) {
		return false;
	}
	if (a.nume < b.nume) {
		return false;
	} else {
		return true;
	}
}

class solver {
	public:
		int N = 0, M;
		Hashtable<std::string, int>  *hash;
		Hashtable<int, std::string>  *hash2;
		ListGraph<int> *list;
		ListGraph<int> *listT;
		std::vector<sofer*> drivers;
		solver(){
			M = 0;
		}
		~solver() {
			delete list;
			delete listT;
			delete hash;
			delete hash2;
		}
		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			 fin >> N >> M;
			 std::string s;
			 hash = new Hashtable<std::string, int>(N, &hashfunction);
			hash2 = new Hashtable<int, std::string>(N, &hashf);
			list = new ListGraph<int>(N);
			listT = new ListGraph<int>(N);
			for (int i = 0; i < N; ++i) {
				fin >> s;
				hash->put(s,i);
				hash2->put(i,s);
			}
			std::string a, b;
			for (int i = 0; i < M; ++i) {
				fin >> a >> b;
        list->addEdge(hash->get(a), hash->get(b));
			}
			int nr;
			fin >> nr;
			bool x = false;
			for (int i = 0; i < nr; ++i) {
				fin >> a;
				fin >> b;
				x = list->is_Path(hash->get(a), hash->get(b));
				if (x) {
					fout << "y\n";
				} else {
					fout << "n\n";
				}
			}

		}

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
				int nr;
				std::string a, b;
				fin >> nr;
				for (int i = 0; i < nr; ++i) {
					fin >> a >> b;
					fout << list->distance(hash->get(a), hash->get(b)) << std::endl;
					//std::cout << "source: " << a << " destination: " << b << " distance: " << list->distance(hash->get(a), hash->get(b)) << std::endl;
				}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int nr, ax, bx;
			char ch;
			std::string a, b;
			int type;
			fin >> nr;
			for (int i = 0; i < nr; ++i) {
				fin >> ch;
				if (ch == 'c') {
					fin >> a >> b >> type;
					ax = hash->get(a);
					bx = hash->get(b);
					if (type == 0) {
						if (!list->hasEdge(ax,bx)) {
							list->addEdge(ax, bx);
						}
					}
					if (type == 1) {
						list->removeEdge(ax, bx);
						list->removeEdge(bx, ax);
					}
					if (type == 2) {
						if (!list->hasEdge(ax, bx)) {
							list->addEdge(ax, bx);
						}
						if (!list->hasEdge(bx, ax)) {
							list->addEdge(bx, ax);
						}
					}
					if (type == 3) {
						if (list->hasEdge(ax, bx) && !list->hasEdge(bx, ax)) {
							list->removeEdge(ax, bx);
							list->addEdge(bx, ax);
						} else {
							if (!list->hasEdge(ax, bx) && list->hasEdge(bx, ax)) {
								list->removeEdge(bx, ax);
								list->addEdge(ax, bx);
							}
						}
					}
				}
				if (ch == 'q') {
					fin >> a >> b >> type;
					ax = hash->get(a);
					bx = hash->get(b);

					if (type == 0) {
						if (list->is_Path(ax, bx)) {
							fout << "y\n";
						} else {
							fout << "n\n";
						}
					}

					if (type == 1) {
						fout << list->distance(ax, bx) << "\n";
					}
					if (type == 2) {
						std::string intermediar;
						fin >> intermediar;
						int d1, d2;
						d1 = list->distance(ax, hash->get(intermediar));
						d2 = list->distance(hash->get(intermediar), bx);
						if (d1 == -1 || d2 == -1) {
							fout << -1 << "\n";
						} else {
						 fout << d1+d2 << "\n";
					 	}
					}
				}
			}
		}

		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			std::priority_queue<sofer> pr;
			std::string ch, start, end, nume_sofer, punctStart;
			int ratingOferit, nr;

			fin >> nr;
			for (int i = 0; i < nr; ++i) {
				fin >> ch;
				if (ch == "d") {
					fin >> nume_sofer >> punctStart;
					bool b = true;
					for (unsigned int j = 0; j < drivers.size(); ++j) {
						if (drivers[j]->nume == nume_sofer) {
							drivers[j]->online = true;
							drivers[j]->locatieActuala = punctStart;
							b = false;
							break;
						}
					}
					if (b) {
						sofer* nou = new sofer(punctStart, nume_sofer);
						drivers.push_back(nou);
					}
				}
				if (ch == "b") {
					fin >> nume_sofer;
					for (unsigned int j = 0; j < drivers.size(); ++j) {
						if (drivers[j]->nume == nume_sofer) {
							drivers[j]->online = false;
							break;
						}
					}
				}
				if (ch == "r") {
					fin >> start >> end >> ratingOferit;
					for (unsigned int j = 0; j < drivers.size(); ++j) {
						if (drivers[j]->online) {
							drivers[j]->departareDeStart =
							list->distance(hash->get(drivers[j]->locatieActuala), hash->get(start));
						}
					}
					for (unsigned int j = 0; j < drivers.size(); ++j) {
						if (drivers[j]->online) {
							pr.push(*drivers[j]);
						}
					}
					if (pr.top().departareDeStart == -1) {
						fout << "Soferi indisponibili" << std::endl;
					} else {
						if (list->is_Path(hash->get(start), hash->get(end))) {
							for (unsigned int j = 0; j < drivers.size(); ++j) {
								if (drivers[j]->nume == pr.top().nume) {
									drivers[j]->distantaTotala +=
									list->distance(hash->get(drivers[j]->locatieActuala), hash->get(start))
									+ list->distance(hash->get(start), hash->get(end));
									drivers[j]->rating += ratingOferit;
									drivers[j]->nrCurse++;
									drivers[j]->medie = (float) drivers[j]->rating/(float) drivers[j]->nrCurse;
									drivers[j]->locatieActuala = end;
									break;
								}
							}
						} else {
							if (list->destination(hash, list, start, end) == -1) {
								fout << "Destinatie inaccesibila" << std::endl;
							} else {
								end = hash2->get(list->destination(hash, listT, start, end));
								for (unsigned int j = 0; j < drivers.size(); ++j) {
									if (drivers[j]->nume == pr.top().nume) {
										drivers[j]->distantaTotala +=
										list->distance(hash->get(drivers[j]->locatieActuala), hash->get(start))
										+ list->distance(hash->get(start), hash->get(end));
										drivers[j]->rating += ratingOferit;
										drivers[j]->nrCurse++;
										drivers[j]->medie = (float) drivers[j]->rating/(float) drivers[j]->nrCurse;
										drivers[j]->locatieActuala = end;
										break;
									}
								}
							}
						}
					}
				}
				if (ch == "top_rating") {
					int nr_soferi;
					fin >> nr_soferi;
					for (unsigned int j = 0; j < drivers.size() - 1; ++j) {
						for (unsigned int k = j + 1; k < drivers.size(); ++k) {
							if (drivers[j]->medie < drivers[k]->medie) {
								sofer* aux;
								aux = drivers[j];
								drivers[j] = drivers[k];
								drivers[k] = aux;
							}
						}
					}
					for (int j = 0; j < min(drivers.size(), nr_soferi); ++j) {
						fout << drivers[j]->nume << ":" << std::fixed << std::setprecision(2) << drivers[j]->medie << " ";
					}
					fout << std::endl;
				}
				if (ch == "top_dist") {
					int nr_soferi;
					fin >> nr_soferi;
					for (unsigned int j = 0; j < drivers.size() - 1; ++j) {
						for (unsigned int k = j + 1; k < drivers.size(); ++k) {
							if (drivers[j]->distantaTotala < drivers[k]->distantaTotala) {
								sofer* aux;
								aux = drivers[j];
								drivers[j] = drivers[k];
								drivers[k] = aux;
							}
						}
					}
					for (int j = 0; j < min(drivers.size(), nr_soferi); ++j) {
						fout << drivers[j]->nume << ":" << drivers[j]->distantaTotala << " ";
					}
					fout << std::endl;
				}
				if (ch == "top_rides") {
					int nr_soferi;
					fin >> nr_soferi;
					for (unsigned int j = 0; j < drivers.size() - 1; ++j) {
						for (unsigned int k = j + 1; k < drivers.size(); ++k) {
							if (drivers[j]->nrCurse < drivers[k]->nrCurse) {
								sofer* aux;
								aux = drivers[j];
								drivers[j] = drivers[k];
								drivers[k] = aux;
							}
						}
					}
					for (int j = 0; j < min(drivers.size(), nr_soferi); ++j) {
						fout << drivers[j]->nume << ":" << drivers[j]->nrCurse << " ";
					}
					fout << std::endl;
				}
				if (ch == "info") {
					std::string nume_sofer;
					fin >> nume_sofer;
					for (unsigned int j = 0; j < drivers.size(); ++j) {
						if (drivers[j]->nume == nume_sofer) {
							fout << nume_sofer << ": " << drivers[j]->locatieActuala
							<< " "<< std::fixed << std::setprecision(2)  << drivers[j]->medie
							<< " " << drivers[j]->nrCurse << " " << drivers[j]->distantaTotala;
							if (drivers[j]->online) {
								fout << " online" << std::endl;
							} else {
								fout << " offline" << std::endl;
							}
							break;
						}
					}
				}
				while(!pr.empty()) {
					pr.pop();
				}
			}

		}

		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
			int combustibil, nr;
			std::string nume_sofer, locatie, locatieSofer, aux;
			std::vector<std::string> vec;
			fin >> combustibil;
			fin >> nume_sofer;
			fin >> nr;
			for (unsigned int i = 0; i < drivers.size(); ++i) {
				if (drivers[i]->nume == nume_sofer) {
					locatieSofer = drivers[i]->locatieActuala;
					break;
				}
			}
			for (int i = 0; i < nr; ++i) {
				fin >> locatie;
				if (list->distance(hash->get(locatieSofer), hash->get(locatie)) != -1
				&&  list->distance(hash->get(locatieSofer), hash->get(locatie)) <= combustibil) {
					vec.push_back(locatie);
				}
			}
			for (unsigned int i = 0; i < vec.size() - 1; ++i) {
				for (unsigned int j = i + 1; j < vec.size(); ++j) {
					if (list->distance(hash->get(locatieSofer), hash->get(vec[i])) ==
						list->distance(hash->get(locatieSofer), hash->get(vec[j]))) {
								if (vec[i] > vec[j]) {
									aux = vec[i];
									vec[i] = vec[j];
									vec[j] = aux;
								}
					} else {
							if (list->distance(hash->get(locatieSofer), hash->get(vec[i])) >
								list->distance(hash->get(locatieSofer), hash->get(vec[j]))) {
										aux = vec[i];
										vec[i] = vec[j];
										vec[j] = aux;
							}
					}
				}
			}
			for (unsigned int i = 0; i < vec.size(); ++i) {
				if (vec[i] == vec[i + 1]) {
					continue;
				}
				fout << vec[i] << std::endl;
			}
		}
};
