package com.nickebert.centipede.utils;

public class GridPoint {
    public int row, col;

    public GridPoint(int row, int col){
        this.row = row;
        this.col = col;
    }

    public GridPoint(GridPoint gp){
        this.row = gp.row;
        this.col = gp.col;
    }
}
