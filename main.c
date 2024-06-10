#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien
typedef struct{
    int no;
    char nama[255];
    char alamat[255];
    char kota[255];
    char tempat_lahir[255];
    char tanggal_lahir[255];
    int umur;
    char noBPJS[12];
    char id[11];
    struct dataPasien *next;
} dataPasien;
dataPasien *head_dataPasien = NULL;

//No,Aktivitas,Biaya (Rp)
typedef struct{
    int no;
    char aktivitas[255];
    int biaya;
    struct biayaTindakan *next;
} biayaTindakan;
biayaTindakan *head_biayaTindakan = NULL;

//No,Tanggal,ID Pasien,Diagnosis,Tindakan,Kontrol,Biaya (Rp)
typedef struct{
    int no;
    char tanggal[255];
    char id[255];
    char diagnosis[255];
    char tindakan[255];
    char kontrol[255];
    int biaya;
    struct riwayatDatang *next;
} riwayatDatang;
riwayatDatang *head_riwayatDatang = NULL;

void bacaDataPasien(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak ada %s\n", filename);
        return;
    }
    char line[255];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token;
        dataPasien *newNode = (dataPasien *)malloc(sizeof(dataPasien));
        token = strtok(line, ",");
        newNode->no = atoi(token);

        token = strtok(NULL, ",");
        strcpy(newNode->nama, token);

        token = strtok(NULL, ",");
        strcpy(newNode->alamat, token);

        token = strtok(NULL, ",");
        strcpy(newNode->kota, token);

        token = strtok(NULL, ",");
        strcpy(newNode->tempat_lahir, token);

        token = strtok(NULL, ",");
        strcpy(newNode->tanggal_lahir, token);

        token = strtok(NULL, ",");
        newNode->umur = atoi(token);

        token = strtok(NULL, ",");
        strcpy(newNode->noBPJS, token);

        token = strtok(NULL, ",");
        strcpy(newNode->id, token);

        newNode->next = NULL;
        if (head_dataPasien == NULL) {
            head_dataPasien = newNode;
        } 
        else {
            dataPasien *temp = head_dataPasien;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
}

void bacaRiwayatDatang(char *filename) {
    // int no;
    // char tangga[255];
    // char id[255];
    // char diagnosis[255];
    // char tindakan[255];
    // char kontrol[255];
    // int biaya;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak ada %s\n", filename);
        return;
    }
    char line[255];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token;
        riwayatDatang *newNode = (riwayatDatang *)malloc(sizeof(riwayatDatang));
        token = strtok(line, ",");
        newNode->no = atoi(token);

        token = strtok(NULL, ",");
        strcpy(newNode->tanggal, token);

        token = strtok(NULL, ",");
        strcpy(newNode->id, token);

        token = strtok(NULL, ",");
        strcpy(newNode->diagnosis, token);

        token = strtok(NULL, ",");
        strcpy(newNode->tindakan, token);

        token = strtok(NULL, ",");
        strcpy(newNode->kontrol, token);

        token = strtok(NULL, ",");
        newNode->biaya = atoi(token);

        newNode->next = NULL;
        if (head_riwayatDatang == NULL) {
            head_riwayatDatang = newNode;
        } 
        else {
            riwayatDatang *temp = head_riwayatDatang;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
}

void bacaBiayaTindakan(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak ada %s\n", filename);
        return;
    } 
    char line[255];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token;
        biayaTindakan *newNode = (biayaTindakan *)malloc(sizeof(biayaTindakan));
        token = strtok(line, ",");
        newNode->no = atoi(token);

        token = strtok(NULL, ",");
        strcpy(newNode->aktivitas, token);

        token = strtok(NULL, ",");
        newNode->biaya = token;

        newNode->next = NULL;
        if (head_biayaTindakan == NULL) {
            head_biayaTindakan = newNode;
        } 
        else {
            biayaTindakan *temp = head_biayaTindakan;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
}


//buat cek isi linked list sesuain aj nanti sama data strukturny
// void printLinkedList() {
//     biayaTindakan *current = head_biayaTindakan;
//     while (current != NULL) {
//         printf("| %-2d | %-15s | %-18d|\n",
//                current->no, current->aktivitas, current->biaya);
//         current = current->next;
//     }
// }



void rapikanFormat() {
    char temp_tanggal[100];
    char temp_tahun[10];
    char temp_bulan[16];
    char tahun[20];
    dataPasien *current = head_dataPasien;

    while (current != NULL) {
        // If the date already contains the full month name and a 4-digit year, skip it
        if (strchr(current->tanggal_lahir, '-') == NULL && strlen(current->tanggal_lahir) > 10) {
            current = current->next;
            continue;
        }

        // Extract day
        temp_tanggal[0] = current->tanggal_lahir[0];
        temp_tanggal[1] = current->tanggal_lahir[1];
        temp_tanggal[2] = ' ';
        temp_tanggal[3] = '\0'; // Null-terminate the string

        // Determine the month and translate to full Indonesian month name
        if (strstr(current->tanggal_lahir, "Jan") != NULL) {
            strcpy(temp_bulan, "Januari ");
        } else if (strstr(current->tanggal_lahir, "Feb") != NULL) {
            strcpy(temp_bulan, "Februari ");
        } else if (strstr(current->tanggal_lahir, "Mar") != NULL) {
            strcpy(temp_bulan, "Maret ");
        } else if (strstr(current->tanggal_lahir, "Apr") != NULL) {
            strcpy(temp_bulan, "April ");
        } else if (strstr(current->tanggal_lahir, "Mei") != NULL) {
            strcpy(temp_bulan, "Mei ");
        } else if (strstr(current->tanggal_lahir, "Jun") != NULL) {
            strcpy(temp_bulan, "Juni ");
        } else if (strstr(current->tanggal_lahir, "Jul") != NULL) {
            strcpy(temp_bulan, "Juli ");
        } else if (strstr(current->tanggal_lahir, "Agu") != NULL) {
            strcpy(temp_bulan, "Agustus ");
        } else if (strstr(current->tanggal_lahir, "Sep") != NULL) {
            strcpy(temp_bulan, "September ");
        } else if (strstr(current->tanggal_lahir, "Okt") != NULL) {
            strcpy(temp_bulan, "Oktober ");
        } else if (strstr(current->tanggal_lahir, "Nov") != NULL) {
            strcpy(temp_bulan, "November ");
        } else if (strstr(current->tanggal_lahir, "Des") != NULL) {
            strcpy(temp_bulan, "Desember ");
        }

        // Extract the year part
        if (strrchr(current->tanggal_lahir, '-') != NULL) {
            strcpy(temp_tahun, strrchr(current->tanggal_lahir, '-') + 1);
        } else if (strrchr(current->tanggal_lahir, ' ') != NULL) {
            strcpy(temp_tahun, strrchr(current->tanggal_lahir, ' ') + 1);
        }

        // Convert the year to a 4-digit year
        int year = atoi(temp_tahun);
        if (year <= 24) {
            sprintf(tahun, "20%02d", year);
        } else {
            sprintf(tahun, "19%02d", year);
        }

        // Construct the new date string
        strcat(temp_tanggal, temp_bulan);
        strcat(temp_tanggal, tahun);
        strcpy(current->tanggal_lahir, temp_tanggal);

        current = current->next;
    }
}


void printLinkedList() {
    printf("| No | Nama Lengkap     | Alamat             | Kota          | Tempat Lahir   | Tanggal Lahir | Umur | No BPJS    | ID        |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    dataPasien *current = head_dataPasien;
    while (current != NULL) {
        printf("| %-2d | %-15s | %-18s | %-13s | %-14s | %-13s | %-4d | %-10s | %-9s |\n",
               current->no, current->nama, current->alamat, current->kota, current->tempat_lahir,
               current->tanggal_lahir, current->umur, current->noBPJS, current->id);
        current = current->next;
    }
}

int main() {
    bacaDataPasien("DataPMC20232024 - Data Pasien.csv");
    bacaBiayaTindakan("DataPMC20232024 - Biaya Tindakan.csv");
    bacaRiwayatDatang("DataPMC20232024 - Riwayat Datang, Diag,, Tindakan.csv");
    rapikanFormat();
    printLinkedList();
    return 0;
}
