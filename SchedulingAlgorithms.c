// jay maa bhavani       shree ganeshay nam:      jay hanumandadani

#include <stdio.h>
#include <stdlib.h>

void display(int *pid, int *art, int *brt, int *pr, int *ft, int c)
{
    printf("\n\n");
    printf("table of process\n");

    printf("|PID |   | AT |  | BT |   | PR |    | FT |   | TAT |   | VT |  \n");

    for (int i = 0; i < c; i++)
    {
        printf("  %d        %d       %d       %d        %d        %d       %d   \n", pid[i], art[i], brt[i], pr[i], ft[i], ft[i] - art[i], ft[i] - art[i] - brt[i]);
    }
}

struct node
{
    int id;
    int start;
    int end;
    struct node *next;
};

struct node1
{
    int data1;
    struct node1 *next1;
};

void sw(int *a, int *b)
{
    // for: swap the two numbers.
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *aray, int n)
{
    // sort the  array using this functiom.

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (aray[i] > aray[j])
            {
                sw(&aray[i], &aray[j]);
            }
        }
    }
}

float AVT(int *finishTime, int *arrivalTime, int *burstTime, int c)
{
    // for: Average Waiting Time

    printf("\n");

    double sum = 0;
    for (int i = 0; i < c; i++)
    {
        sum += (finishTime[i] - arrivalTime[i] - burstTime[i]);
    }

    return sum / c;
}

// link
float ATT(int *finishTime, int *arrivalTime, int c)
{
    // for: Average Turnaround Time

    double sum = 0;
    for (int i = 0; i < c; i++)
    {
        sum += (finishTime[i] - arrivalTime[i]);
    }

    return (sum / c);
}

void FIFS(int *art, int *brt, int *pr, int *pid, int c)
{

    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            if (art[i] > art[j])
            {

                sw(&art[i], &art[j]);
                sw(&brt[i], &brt[j]);
                sw(&pid[i], &pid[j]);
                sw(&pr[i], &pr[j]);
            }
        }
    }

    int current = 0;

    int ft[c]; // finish time of process

    for (int i = 0; i < c; i++)
    {
        ft[i] = 0;
    }

    printf(" PROCESS EXECUTION CHART: ");

    printf("START: ");
    for (int i = 0; i < c; i++)
    {
        printf("p%d --> ", pid[i]);
    }
    printf(" (END)");

    printf("\n GANT CHART : ");

    printf("0 ");

    for (int j = 0; j < c; j++)
    {

        if (art[j] <= current)
        {
            current += brt[j];
            printf("|p%d| %d ", pid[j], current);

            ft[j] = current;
        }
        else
        {

            printf(" %d ", art[j]);
            current = art[j];
            printf(" |p%d| %d ", pid[j], current + brt[j]);
            current += brt[j];

            ft[j] = current;
        }
    }

    printf("\n Average Waiting Time is: %f  ", AVT(&ft[0], art, brt, c));
    printf("\n\n Average Turnaround Time %f ", ATT(&ft[0], art, c));
    display(pid, art, brt, pr, &ft[0], c);
}

void SJF(int *art, int *brt, int *pr, int *pid, int c)
{

    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            if (brt[i] > brt[j])
            {

                sw(&art[i], &art[j]);
                sw(&brt[i], &brt[j]);
                sw(&pid[i], &pid[j]);
                sw(&pr[i], &pr[j]);
            }
        }
    }

    struct node *head = NULL;
    struct node *ptr = NULL;
    struct node *temp = NULL;

    int ft[c]; // finish time of process
    int cm[c]; // process complete or not

    for (int i = 0; i < c; i++)
    {
        ft[i] = 0;
        cm[i] = 0;
    }

    int time = art[0];
    int current = 0;
    int complete = 0;

    while (complete != c)
    {

        for (int i = 0; i < c; i++)
        {

            if (art[i] <= current && cm[i] == 0)
            {
                complete++;
                ft[i] = current + brt[i];
                current = current + brt[i];
                cm[i] = 1;

                if (head == NULL)
                {
                    ptr = (struct node *)malloc(sizeof(struct node));
                    ptr->id = pid[i];
                    ptr->end = current;
                    ptr->start = current - brt[i];
                    ptr->next = NULL;
                    head = ptr;
                }
                else
                {
                    ptr->next = (struct node *)malloc(sizeof(struct node));
                    ptr = ptr->next;
                    ptr->id = pid[i];
                    ptr->end = current;
                    ptr->start = current - brt[i];
                    ptr->next = NULL;
                }
                break;
            }
            else
            {
                if (time >= art[i] && cm[i] == 0)
                {
                    time = art[i];
                }
            }
        }

        if (current < time)
        {
            current = time;
        }
    }

    struct node *pt = head;

    printf(" PROCESS EXECUTION CHART: ");

    printf("(START) ");
    while (pt != NULL)
    {
        printf("p%d --> ", (pt->id));
        pt = pt->next;
    }
    printf(" (END)");

    struct node *pt2 = head;

    printf("\n GANT CHART:");

    if (pt2->start != 0)
    {
        printf("0 %d", pt2->start);
    }
    else
    {
        printf("0");
    }

    while (pt2 != NULL)
    {
        printf(" |p%d| ", (pt2->id));

        if (pt2->next == NULL || pt2->end == pt2->next->start)
        {
            printf("%d", (pt2->end));
        }
        else
        {
            printf("%d %d", (pt2->end), pt2->next->end);
        }
        pt2 = pt2->next;
    }

    printf("\n Average Waiting Time is: %f  ", AVT(&ft[0], art, brt, c));
    printf("\n Average Turnaround %f ", ATT(&ft[0], art, c));

    display(pid, art, brt, pr, &ft[0], c);
}

// shortest remaining time first;
void SRTF(int *art, int *brt, int *pr, int *pid, int c)
{

    int cbrt[c]; // copy burst time;
    for (int i = 0; i < c; i++)
    {
        cbrt[i] = brt[i];
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {

            if (brt[i] > brt[j])
            {

                sw(&art[i], &art[j]);
                sw(&brt[i], &brt[j]);
                sw(&pid[i], &pid[j]);
                sw(&pr[i], &pr[j]);
                sw(&cbrt[i], &cbrt[j]);
            }
        }
    }

    int n = 0;

    struct node1 *head = NULL;
    struct node1 *ptr = NULL;
    struct node1 *temp = NULL;

    for (int i = 0; i < c; i++)
    {

        if (head == NULL)
        {
            ptr = (struct node1 *)malloc(sizeof(struct node1));
            ptr->data1 = art[i];
            ptr->next1 = NULL;
            head = ptr;
            n++;
        }
        else
        {

            temp = head;

            int t = 1;
            while (temp != NULL)
            {
                if (art[i] == temp->data1)
                {
                    t = 0;
                    break;
                }

                temp = temp->next1;
            }

            if (t == 1)
            {
                ptr->next1 = (struct node1 *)malloc(sizeof(struct node));
                ptr = ptr->next1;
                ptr->data1 = art[i];
                ptr->next1 = NULL;
                n++;
            }
        }
    }
    printf("\n");

    int arr[n]; // set of arrival time ( means unique value )
    int l = 0;
    temp = head;

    while (temp != NULL)
    {
        arr[l] = temp->data1;
        temp = temp->next1;
        l++;
    }
    printf("\n");

    sort(&arr[0], n);

    int ft[c]; // finish time of process
    int cm[c]; // process complete or not

    for (int i = 0; i < c; i++)
    {
        ft[i] = 0;
        cm[i] = 0;
    }

    int time = 0; // current time

    printf(" Gantt Chart: ");
    if (arr[0] > 0 && c > 0)
    {
        // w means wait
        printf("0 |W| %d", arr[0]);
        time = arr[0];
    }
    else
    {
        printf("0 ");
    }

    int complete = 0;

    for (int i = 0; i < n - 1; i++)
    {

        int fmin = arr[i];     // first minimum arrival time
        int smin = arr[i + 1]; // second minimum arrival time;
    jump:
        for (int j = 0; j < c; j++)
        {
            if (cm[j] == 0)
            {

                if (art[j] <= time)
                {

                    if (brt[j] < smin - fmin)
                    {
                        time += brt[j];
                        printf("|p%d| %d", pid[j], time);
                        ft[j] = time;
                        cm[j] = 1;
                        complete++;
                        fmin = time;
                        goto jump;
                    }
                    else if (brt[j] == smin - fmin)
                    {
                        time += brt[j];
                        printf("|p%d| %d", pid[j], time);
                        ft[j] = time;
                        cm[j] = 1;
                        complete++;
                        break;
                    }
                    else
                    {
                        brt[j] -= (smin - fmin);
                        time = smin;
                        printf("|p%d| %d", pid[j], time);

                        break;
                    }
                }
            }
        }

        for (int k = 0; k < c; k++)
        {

            for (int j = k + 1; j < c; j++)
            {

                if (brt[k] > brt[j])
                {

                    sw(&art[k], &art[j]);
                    sw(&brt[k], &brt[j]);
                    sw(&pid[k], &pid[j]);
                    sw(&pr[k], &pr[j]);
                    sw(&ft[k], &ft[j]);
                    sw(&cm[k], &cm[j]);
                    sw(&cbrt[k], &cbrt[j]);
                }
            }
        }
    }

    if (complete != c)
    {

        for (int i = 0; i < c; i++)
        {
            if (cm[i] == 0)
            {
                time += brt[i];
                printf("|p%d| %d", pid[i], time);
                complete++;
                cm[i] == 1;
                ft[i] = time;
            }
        }
    }

    printf("\n Average Waiting Time is: %f  ", AVT(&ft[0], art, cbrt, c));
    printf("\n Average Turnaround %f ", ATT(&ft[0], art, c));
    display(pid, art, cbrt, pr, &ft[0], c);
}

void NPPS(int *art, int *brt, int *pr, int *pid, int c)
{
    // Non Preemptive Priority Scheduling

    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            if (pr[i] > pr[j])
            {

                sw(&art[i], &art[j]);
                sw(&brt[i], &brt[j]);
                sw(&pid[i], &pid[j]);
                sw(&pr[i], &pr[j]);
            }
        }
    }

    struct node *head = NULL;
    struct node *ptr = NULL;
    struct node *temp = NULL;

    int ft[c]; // finish time of process
    int cm[c]; // process complete or not

    for (int i = 0; i < c; i++)
    {
        ft[i] = 0;
        cm[i] = 0;
    }

    int time = art[0];
    int current = 0;
    int complete = 0;

    while (complete != c)
    {

        for (int i = 0; i < c; i++)
        {

            if (art[i] <= current && cm[i] == 0)
            {
                complete++;
                ft[i] = current + brt[i];
                current = current + brt[i];
                cm[i] = 1;

                if (head == NULL)
                {
                    ptr = (struct node *)malloc(sizeof(struct node));
                    ptr->id = pid[i];
                    ptr->end = current;
                    ptr->start = current - brt[i];
                    ptr->next = NULL;
                    head = ptr;
                }
                else
                {
                    ptr->next = (struct node *)malloc(sizeof(struct node));
                    ptr = ptr->next;
                    ptr->id = pid[i];
                    ptr->end = current;
                    ptr->start = current - brt[i];
                    ptr->next = NULL;
                }
                break;
            }
            else
            {
                if (time >= art[i] && cm[i] == 0)
                {
                    time = art[i];
                }
            }
        }

        if (current < time)
        {
            current = time;
        }
    }

    struct node *pt = head;

    printf(" PROCESS EXECUTION CHART: ");

    printf("(START) ");
    while (pt != NULL)
    {
        printf("p%d --> ", (pt->id));
        pt = pt->next;
    }
    printf(" (END)");

    struct node *pt2 = head;

    printf("\n GANT CHART:");

    if (pt2->start != 0)
    {
        printf("0 %d", pt2->start);
    }
    else
    {
        printf("0");
    }

    while (pt2 != NULL)
    {
        printf(" |p%d| ", (pt2->id));

        if (pt2->next == NULL || pt2->end == pt2->next->start)
        {
            printf("%d", (pt2->end));
        }
        else
        {
            printf("%d %d", (pt2->end), pt2->next->end);
        }
        pt2 = pt2->next;
    }

    printf("\n Average Waiting Time is: %f  ", AVT(&ft[0], art, brt, c));
    printf("\n Average Turnaround %f ", ATT(&ft[0], art, c));
    display(pid, art, brt, pr, &ft[0], c);
}

void PPS(int *art, int *brt, int *pr, int *pid, int c)
{
    // Preemptive Priority Scheduling

    int cbrt[c]; // copy burst time;
    for (int i = 0; i < c; i++)
    {
        cbrt[i] = brt[i];
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {

            if (pr[i] > pr[j])
            {

                sw(&art[i], &art[j]);
                sw(&brt[i], &brt[j]);
                sw(&pid[i], &pid[j]);
                sw(&pr[i], &pr[j]);
                sw(&cbrt[i], &cbrt[j]);
            }
        }
    }

    int n = 0;

    struct node1 *head = NULL;
    struct node1 *ptr = NULL;
    struct node1 *temp = NULL;

    for (int i = 0; i < c; i++)
    {

        if (head == NULL)
        {
            ptr = (struct node1 *)malloc(sizeof(struct node1));
            ptr->data1 = art[i];
            ptr->next1 = NULL;
            head = ptr;
            n++;
        }
        else
        {

            temp = head;

            int t = 1;
            while (temp != NULL)
            {
                if (art[i] == temp->data1)
                {
                    t = 0;
                    break;
                }

                temp = temp->next1;
            }

            if (t == 1)
            {
                ptr->next1 = (struct node1 *)malloc(sizeof(struct node));
                ptr = ptr->next1;
                ptr->data1 = art[i];
                ptr->next1 = NULL;
                n++;
            }
        }
    }
    printf("\n");

    int arr[n]; // set of arrival time ( means unique value )
    int l = 0;
    temp = head;

    while (temp != NULL)
    {
        arr[l] = temp->data1;
        temp = temp->next1;
        l++;
    }
    printf("\n");

    sort(&arr[0], n);

    int ft[c]; // finish time of process
    int cm[c]; // process complete or not

    for (int i = 0; i < c; i++)
    {
        ft[i] = 0;
        cm[i] = 0;
    }

    int time = 0; // current time

    printf(" Gantt Chart: ");
    if (arr[0] > 0 && c > 0)
    {
        // w means wait
        printf("0 |W| %d", arr[0]);
        time = arr[0];
    }
    else
    {
        printf("0 ");
    }

    int complete = 0;

    for (int i = 0; i < n - 1; i++)
    {

        int fmin = arr[i];     // first minimum arrival time
        int smin = arr[i + 1]; // second minimum arrival time;
    jump:
        for (int j = 0; j < c; j++)
        {
            if (cm[j] == 0)
            {

                if (art[j] <= time)
                {

                    if (brt[j] < smin - fmin)
                    {
                        time += brt[j];
                        printf("|p%d| %d", pid[j], time);
                        ft[j] = time;
                        cm[j] = 1;
                        complete++;
                        fmin = time;
                        goto jump;
                    }
                    else if (brt[j] == smin - fmin)
                    {
                        time += brt[j];
                        printf("|p%d| %d", pid[j], time);
                        ft[j] = time;
                        cm[j] = 1;
                        complete++;
                        break;
                    }
                    else
                    {
                        brt[j] -= (smin - fmin);
                        time = smin;
                        printf("|p%d| %d", pid[j], time);

                        break;
                    }
                }
            }
        }

        for (int k = 0; k < c; k++)
        {

            for (int j = k + 1; j < c; j++)
            {

                if (pr[k] > pr[j])
                {

                    sw(&art[k], &art[j]);
                    sw(&brt[k], &brt[j]);
                    sw(&pid[k], &pid[j]);
                    sw(&pr[k], &pr[j]);
                    sw(&ft[k], &ft[j]);
                    sw(&cm[k], &cm[j]);
                    sw(&cbrt[k], &cbrt[j]);
                }
            }
        }
    }

    if (complete != c)
    {

        for (int i = 0; i < c; i++)
        {
            if (cm[i] == 0)
            {
                time += brt[i];
                printf("|p%d| %d", pid[i], time);
                complete++;
                cm[i] == 1;
                ft[i] = time;
            }
        }
    }

    printf("\n Average Waiting Time is: %f  ", AVT(&ft[0], art, cbrt, c));
    printf("\n Average Turnaround %f ", ATT(&ft[0], art, c));

    display(pid, art, cbrt, pr, &ft[0], c);
}

void RR(int *art, int *brt, int *pr, int *pid, int count2, int cs)
{
    // cs - context switching
    int qt;
    printf(" ENTER  THE VALUE OF QUANTUM TIME: ");
    scanf("%d", &qt);

    printf("\n");
    printf(" Gantt Chart: ");
    int com = 0;
    int ct = 0;

    int check;

    int ft[count2];
    int wt[count2];
    int tat[count2];
    int rt[count2];

    for (int i = 0; i < count2; i++)
    {
        rt[i] = brt[i];
    }

    while (com != count2)
    {

        check = 0;
        for (int i = 0; i < count2; i++)
        {

            if (art[i] <= ct && rt[i] > 0)
            {
                if (rt[i] <= qt)
                {
                    com++;
                    ct += rt[i];
                    ft[i] = ct;

                    tat[i] = ft[i] - art[i];
                    wt[i] = tat[i] - brt[i];
                    for (int j = 0; j < rt[i]; j++)
                    {
                        printf(" P%d", i + 1);
                    }
                    rt[i] = 0;
                }
                else
                {
                    ct += qt;
                    for (int j = 0; j < qt; j++)
                    {
                        printf(" P%d", i + 1);
                    }
                    rt[i] -= qt;
                }
                check = 1;
            }
            /*else{
                com++;
            }*/
        }
        if (check == 0)
        {
            ct++;
            printf(" e");
        }
    }
    for (int i = 0; i < count2; i++)
    {
        tat[i] = ft[i] - art[i];
    }
    printf("\n\n");

    printf(" Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");

    for (int i = 0; i < count2; i++)
    {
        printf("  %d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d\n", pr[i], art[i], brt[i], ft[i],
               tat[i], wt[i]);
    }
    float sum1 = 0;
    float sum2 = 0;
    for (int i = 0; i < count2; i++)
    {
        sum1 += tat[i];
        sum2 += wt[i];
    }
    printf(" Average Turn Around Time is: %.2f\n", sum1 /

                                                       count2);

    printf(" Average Waiting Time is: %.2f\n", sum2 /

                                                   count2);
}
int main()
{

    FILE *fp = NULL;

    fp = fopen("inputfile.txt", "r+");

    printf("ProcessID  ");
    char ch;
    ch = fgetc(fp);
    while (!feof(fp) && ch != '\n')
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    printf("\n");

    int number;

    int *art = (int *)malloc(15 * sizeof(int)); // arrival time
    int *brt = (int *)malloc(15 * sizeof(int)); // burst time (time taken by process)
    int *pr = (int *)malloc(15 * sizeof(int));  // priority of process
    int *pid = (int *)malloc(15 * sizeof(int)); // process id 1,2,3,..,n
    int n = 15;
    // initially we assume total 15 process , if it is more than that then  we allocate memory
    // by using realloc

    int count = 0;

    while (fscanf(fp, "%d", &number) == 1)
    {

        art[count / 3] = number;
        fscanf(fp, "%d", &number);
        brt[count / 3] = number;
        fscanf(fp, "%d", &number);
        pr[count / 3] = number;

        pid[count / 3] = (count / 3) + 1;
        count += 3;

        if (count / 3 >= n)
        {
            n += 10;
            art = (int *)realloc(art, n * sizeof(int)); // arrival time
            brt = (int *)realloc(brt, n * sizeof(int)); // burst time (time taken by process)
            pr = (int *)realloc(pr, n * sizeof(int));   // priority of process
            pid = (int *)realloc(pid, n * sizeof(int)); // process id
        }
    }

    for (int j = 0; j < count / 3; j++)
    {
        printf("P%d %d %d %d\n", pid[j], art[j], brt[j], pr[j]);
    }

    ch = fgetc(fp);
    while (!feof(fp) && ch != '\n')
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    printf("\n");

    int contextSwitch;

    fscanf(fp, "%d", &contextSwitch);
    printf(" %d \n", contextSwitch);

    printf("\n\n=*=*=*=*=*=*=*=*=*=!!!  WELCOME TO YOU !!!=*=*=*=*=*=*=*=*=*=\n\n");
lable:
    printf(" Enter 1: First Come First Served (FCFS)\n");
    printf(" Enter 2: Shortest Job First (SJF)\n");
    printf(" Enter 3: Shortest Remaining Time First (SRTF)\n");
    printf(" Enter 4: Non Preemptive Priority Scheduling(NPPS)\n");
    printf(" Enter 5: Preemptive Priority Scheduling(PPS)\n");
    printf(" Enter 6: Round Robin (RR)\n");

    int operation;

    printf("\nENTER: ");

    scanf("%d", &operation);
    printf("\n");

    switch (operation)
    {
    case 1:
        FIFS(art, brt, pr, pid, count / 3);
        break;
    case 2:
        SJF(art, brt, pr, pid, count / 3);
        break;
    case 3:
        SRTF(art, brt, pr, pid, count / 3);
        break;
    case 4:
        NPPS(art, brt, pr, pid, count / 3);
        break;
    case 5:
        PPS(art, brt, pr, pid, count / 3);
        break;
    case 6:
        RR(art, brt, pr, pid, count / 3, contextSwitch);
        break;
    default:
        printf(" !!! ERROR , please enter the valid operation\n");
        goto lable;
    }
    printf("\n\n");

    fclose(fp);
    return 0;
}
