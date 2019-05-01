awk '{
        if ($1+$2+$3 > 240) grade="A";
        else if ($1+$2+$3 > 180) grade="B";
        else if ($1+$2+$3 > 120) grade="C";
        else grade="F";
        print $0," : ",grade;
}' marks.txt > grades.txt
