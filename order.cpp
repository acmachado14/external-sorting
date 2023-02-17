#include "arquivo.h"
#include <numeric>
#include <ctime>
#include <queue>

const clock_t begin_time = clock();

bool sortAuxFunciton (Arquivo a, Arquivo b) {
    string aAge = a.age;
    string bAge = b.age;
    if (aAge.compare(bAge) < 0){
        return true;
    }else if (aAge.compare(bAge) > 0){
        return false;
    }else{
        string aValue = a.value;
        string bValue = b.value;
        if (aValue.compare(bValue) < 0){
            return true;
        }else{
            return false;
        }
    }
}

struct HeapNode {
    Arquivo aux;
    int index;
    HeapNode(Arquivo a, int b): aux(a), index(b) {}
    bool operator<(const HeapNode& rhs) const {
        return (sortAuxFunciton(rhs.aux, aux));
    }
};

int input(string input_name, int TOTAL_MEM) {
    FILE *input = fopen(input_name.c_str(), "rb");

    Arquivo c;
    int run_count = 0;
    int total_mem_so_far = 0;

    FILE *output;
    vector<Arquivo> data; data.clear();

    cout << "File " << input_name << " is being read!" << endl;
    cout << "-------------------------------------------------------\n\n\n";
    cout << "-------------------------------------------------------\n";

    Arquivo aux;
    while(!feof(input)){
        if(fread(&aux, sizeof(Arquivo), 1, input)){
            if (total_mem_so_far + sizeof(Arquivo) < TOTAL_MEM) {
                total_mem_so_far += sizeof(Arquivo) + 1;
                data.push_back(aux);
            } else {
                sort(data.begin(), data.end(), sortAuxFunciton);

                run_count++;

                char run[10] = "run_";
                char ss[100];
                snprintf(ss, 100, "%s%d%s", run, run_count, ".dat");

                cout << "Writing " << ss << endl;

                output = fopen(ss, "ab");

                if(!output){
                    cout << "File input is not found!" << endl << "Exit program!" << endl;
                    exit(-1);
                }

                int data_size = data.size();
                for (int i = 0; i < data_size-1; i++) {
                    fwrite(&data[i], sizeof(Arquivo), 1, output);
                }

                if (data_size > 0) {
                    fwrite(&data[data_size-1], sizeof(Arquivo), 1, output);
                }

                fclose(output);
                data.clear();
                total_mem_so_far = sizeof(Arquivo);
                data.push_back(aux);
            }
        }
    }

    if (data.size() > 0) {
        sort(data.begin(), data.end(), sortAuxFunciton);

        run_count++;

        char ss[100];
        snprintf(ss, 100, "%s%d%s", "run_", run_count, ".dat");

        cout << "Writing " << ss << endl;

        output = fopen(ss, "ab");

        for (int i = 0; i < data.size(); i++) {
            fwrite(&data[i], sizeof(Arquivo), 1, output);
        }

        fclose(input);
        fclose(output);
    }


    cout << "Read input is done!" << endl;
    cout << "Entire process so far took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
    cout << "-------------------------------------------------------\n\n\n";

    return run_count;
}

void merge(int start, int end, int location) {
    int runs_count = end - start + 1;

    FILE *input[runs_count];
    char ss[100];
    for (int i = 0; i < runs_count; i++) {
        snprintf(ss, 100, "%s%d%s", "run_", start + i, ".dat");
        input[i] = fopen(ss, "rb");
    }

    priority_queue<HeapNode, vector<HeapNode> > heap;

    for (int i = 0; i < runs_count; i++) {
        Arquivo aux;
        if (!feof(input[i])) {
            if(fread(&aux, sizeof(Arquivo), 1, input[i])){
                heap.push(HeapNode(aux, i));
            }
        }
    }

    cout << "-------------------------------------------------------\n";
    cout << endl << "Merging from run_" << start << " to run_" << end << " into run_" << location << " file" << endl;

    FILE *output;
    snprintf(ss, 100, "%s%d%s", "run_", location, ".dat");
    output = fopen(ss, "ab");

    while (!heap.empty()) {
        Arquivo aux2 = heap.top().aux;
        int index = heap.top().index;
        heap.pop();

        fwrite(&aux2, sizeof(Arquivo), 1, output);

        if (!feof(input[index])) {
            if (fread(&aux2, sizeof(Arquivo), 1, input[index])){
                heap.push(HeapNode(aux2, index));
            }
        }
    }

    cout << "Merge done!" << endl << endl;
    cout << "-------------------------------------------------------\n\n\n";

    for (int i = 0; i < runs_count; i++) {
        fclose(input[i]);
    }

    fclose(output);
}

void merge(int runs_count, string output_name) {

    cout << "-------------------------------------------------------\n";
	cout << "Merging " << runs_count << " files into output (" << output_name << " file)" << endl;
	cout << "-------------------------------------------------------\n\n\n";

    int start = 1;
    int end = runs_count;
    while (start < end) {
        int location = end;
        int distance = 100;
        int time = (end - start + 1) / distance + 1;
        if ((end - start + 1) / time < distance) {
            distance = (end - start + 1) / time + 1;
        }
        while (start <= end) {
            int mid = min(start + distance, end);
            location++;
            merge(start, mid, location);
            start = mid + 1;
        }
        end = location;
    }

    stringstream ss;
    ss << "run_" << start << ".dat";
    rename(ss.str().c_str(), output_name.c_str());

    cout << "-------------------------------------------------------\n";
    cout << "Removing chucks files!" << endl;
    for (int i = 1; i < end; i++) {
        stringstream ss;
        ss << "run_" << i << ".dat";
        cout << "Removing " << ss.str() << endl;
        remove(ss.str().c_str());
    }
    cout << "-------------------------------------------------------\n\n\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "input_file output_file mem_size" << endl << "Exit program!" << endl;
        return 0;
    }

    string input_name = argv[1];
    string output_name = argv[2];
    int TOTAL_MEM = strtol(argv[3], nullptr, 0); // bytes

    int runs_count = input(input_name, TOTAL_MEM);

    merge(runs_count, output_name);

    cout << "Entire process took a total of: " << float(clock() - begin_time) / CLOCKS_PER_SEC * 1000 << " msec." << endl;
    return 0;
}