import { Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { MeteringsModule } from './meterings/meterings.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Meterings } from './meterings/meterings.entity';

@Module({
  imports: [
    ConfigModule.forRoot({
      isGlobal: true,
    }),
    TypeOrmModule.forRootAsync({
      imports: [ConfigModule],
      useFactory: (configService: ConfigService) => ({
        type: 'postgres',
        host: configService.get<string>('DB_HOST'),
        port: configService.get<number>('DB_PORT'),
        username: configService.get<string>('DB_USERNAME'),
        password: configService.get<string>('DB_PASSWORD'),
        database: configService.get<string>('DB_DATABASE'),
        entities: [Meterings],
        synchronize: false,
        logging: true,
      }),
      inject: [ConfigService],
    }),
    // TypeOrmModule.forRoot({
    //   type: 'postgres',
    //   host: 'localhost',
    //   port: 5432,
    //   password: 'postgres',
    //   username: 'postgres',
    //   entities: [Meterings],
    //   database: 'lifaeIOT',
    //   synchronize: true,
    //   logging: true,
    // }),
    MeteringsModule,
  ],
})
export class AppModule {}
