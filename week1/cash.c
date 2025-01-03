#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int monee;
    int tallee = 0;
    int local_tallee = 0;

    do
    {
        monee = get_int("Change Owed: ");
    }
    while (monee < 1 || monee > 100);

    if (monee > 24)
    {
        local_tallee = monee / 25;
        monee -= local_tallee * 25;
        tallee += local_tallee;
    }

    if (monee > 9)
    {
        local_tallee = monee / 10;
        monee -= local_tallee * 10;
        tallee += local_tallee;
    }

    if (monee > 4)
    {
        local_tallee = monee / 5;
        monee -= local_tallee * 5;
        tallee += local_tallee;
    }

    if (monee > 0)
    {
        local_tallee = monee;
        monee -= local_tallee;
        tallee += local_tallee;
    }

    printf("%i\n", tallee);
}
