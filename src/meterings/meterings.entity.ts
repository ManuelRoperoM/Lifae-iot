import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity('meterings') // Nombre de la tabla en la base de datos
export class Meterings {
  @PrimaryGeneratedColumn() // Define una columna de clave primaria que se incrementa automáticamente
  id: number;

  @Column({ type: 'float' })
  activa: number;

  @Column({ type: 'float' })
  reactiva: number;

  @Column({ type: 'float' })
  aparente: number;

  @Column({ type: 'float' })
  fp: number;

  @Column({ type: 'time', nullable: true })
  hora: string;

  @Column({ type: 'date', nullable: true })
  fecha: string;

  @Column({ type: 'float', nullable: true })
  latitude: number;

  @Column({ type: 'float', nullable: true })
  longitude: number;
}
